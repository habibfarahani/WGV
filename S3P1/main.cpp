
#include <stdio.h>
#include <pthread.h>
#include <time.h>           // for timeval
#include <sys/time.h>       // for gettimeofday


// Mutex to complement conditionals above and also protect our counter (when being incremented by each thread);
pthread_mutex_t data_mutex = PTHREAD_MUTEX_INITIALIZER;

// Printf is not reenterant so use a dedicated mutex to protect it
pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;


#define ONE_MINUTE  6000
#define YES_COUNTER     10

// getTime uses only stack variables and uses gettimeofday which is  areenterant function .
// So it should be reentrant and thread safe.
long int getTime()
{
    struct timeval tv;
    long int ms;


    gettimeofday(&tv, NULL);

    ms = (tv.tv_usec / 1000) + (1000 * tv.tv_sec);

    return ms;

}


long int getDiffTime(long int start, long int end)
{
    if(start < end)
    {
        return (end - start);
    }

    return -1;
}

int printCounter(int counter)
{
    if(counter == YES_COUNTER)
    {
        pthread_mutex_lock( &print_mutex );
        printf("YES\n");
        pthread_mutex_unlock( &print_mutex );
    }
    else
    {
        pthread_mutex_lock( &print_mutex );
        printf("NO\n");
        pthread_mutex_unlock( &print_mutex );
    }
}

// This thread prints YES only when the function is called 10 times within a minute.  It will print NO if on the 11th call and onward.
// The counter will reset after one minute.
void MyYesNoFunction()
{
    int stackCounter;
    static int yesNoCounter = 0;        // Call counter
    static long int startTime = 0; 
    static int reSeedTime = 1;
    long int currentTime = getTime(); 
    long int diffTime = 0; 
    
    

    // Lock the data mutex
    pthread_mutex_lock( &data_mutex );
    stackCounter = ++yesNoCounter;
    if(reSeedTime)
    {
        startTime = currentTime;
        reSeedTime = 0;
    }
    // Unlock the counter mutex.
    pthread_mutex_unlock( &data_mutex );

    // Calculate elapsed time
    diffTime = getDiffTime(startTime, currentTime);
    // One minute has not passed yet
    if(diffTime <= ONE_MINUTE)
    {
        printCounter(stackCounter);
    }
    else
    {
        // Lock the data mutex
        pthread_mutex_lock( &data_mutex );
        
        yesNoCounter = 0;       // reset yes / no counter after 1 minute
        reSeedTime = 1;         // Make sure the startTime is reseeded.
                // Unlock the counter mutex.
        pthread_mutex_unlock( &data_mutex );
        // This is the first call after 1 minute so print if it is YES or NO
        printCounter(stackCounter);
        
    }

}



int main(char *argv[], int argc)
{
    char ch;
    int exit = 0;


    printf("Please enter c to make a function call or enter q to quit:");

    while(!exit)
    {
        ch = getchar();

        if(('c' == ch) || ('C' == ch))
        {
            MyYesNoFunction();
        }
        else if(('q' == ch) || ('Q' == ch))
        {
            exit = 1;
        }
    }

    return 0;
}
