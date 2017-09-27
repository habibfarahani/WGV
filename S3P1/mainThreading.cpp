
#include <stdio.h>
#include <pthread.h>
#include <time.h>           // for timeval
#include <sys/time.h>       // for gettimeofday


// Mutex to complement conditionals above and also protect our counter (when being incremented by each thread);
pthread_mutex_t data_mutex = PTHREAD_MUTEX_INITIALIZER;

// Printf is not reenterant so use a dedicated mutex to protect it
pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;



pthread_cond_t timer_cond = PTHREAD_COND_INITIALIZER;

// Mutex to complement conditionals above and also protect our counter (when being incremented by each thread);
pthread_mutex_t timer_mutex = PTHREAD_MUTEX_INITIALIZER;


static long int diffTime = 0; 

#define ONE_MINUTE  60
#define YES_COUNTER     10


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
    

    // Lock the data mutex
    pthread_mutex_lock( &data_mutex );
    stackCounter = ++yesNoCounter;
    // Unlock the counter mutex.
    pthread_mutex_unlock( &data_mutex );

    if(diffTime < ONE_MINUTE)
    {
        printCounter(stackCounter);
    }
    else
    {
        yesNoCounter = 0;       // reset yes / no counter after 1 minute
        printCounter(stackCounter);
        pthread_mutex_lock(&timer_mutex);
        diffTime=0;
        pthread_mutex_unlock(&timer_mutex);
        
    }

}


// Thread to keep time ( every one second)
void *yesNoTimer(void *pArg)
{
    static int reSeedTime = 1;          // Indicates whether start Time should be repopulated
    static long int startTime = 0;      // Heap variable protected by mutex indicating the start of the counter
    struct timespec timeToWait;
    struct timeval now;

    while(1)
    {
        gettimeofday(&now,NULL);
        timeToWait.tv_sec = now.tv_sec + 1;
        timeToWait.tv_nsec = (now.tv_usec+1000UL)*1000UL;
        pthread_mutex_lock(&timer_mutex);
        pthread_cond_timedwait(&timer_cond, &timer_mutex, &timeToWait);
        diffTime++;
        pthread_mutex_unlock(&timer_mutex);

    }        
    return NULL;

}



int main(char *argv[], int argc)
{
    char ch;
    int exit = 0;

    int data = 0;
    pthread_t eyesno_thread;

    // Weonly need to create one thread as the other thread that is going to ping-pong can run i the context
    // of the main thread.
    if(pthread_create(&eyesno_thread, NULL, yesNoTimer, &data)) 
    {
        
        fprintf(stderr, "Error creating even printing thread\n");
        return -1;
    
    }

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
