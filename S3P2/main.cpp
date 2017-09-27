
#include <stdio.h>
#include <pthread.h>

// Conditional var to signal odd or even threads to synchronize with each other
pthread_cond_t odd_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t even_cond = PTHREAD_COND_INITIALIZER;

// Mutex to complement conditionals above and also protect our counter (when being incremented by each thread);
pthread_mutex_t data_mutex = PTHREAD_MUTEX_INITIALIZER;

static int currentNumber = 9;   //an odd number so we should trigger odd thread first

// Thread to print even numbers
void * print_even(void *pArg)
{
    
    while(1)
    {
        // Lock the data mutex
        pthread_mutex_lock( &data_mutex );
        // Is data odd number
        if((currentNumber % 2))
        {
            // It is odd so signal odd thread and wait for data to become even again
            pthread_cond_signal(&odd_cond);
            pthread_cond_wait( &even_cond, &data_mutex ); 
        }
        // The data is even so print it (May be some error checking!)
        printf("EVEN: %10d\n", currentNumber++);
        // Unlock the counter mutex.
        pthread_mutex_unlock( &data_mutex );
    }        
    return NULL;

}


// This thread runs in the context of main thread there is no need to create two sperate thread in this problem.
void  print_odd()
{
    while(1)
    {
        // Lock the data mutex
        pthread_mutex_lock( &data_mutex );
        // Check to see if we have an even number
        if((currentNumber % 2) == 0)
        {
            // Number is even so signal the even thread
            pthread_cond_signal(&even_cond);
            // Wait for the number to become odd again
            pthread_cond_wait( &odd_cond, &data_mutex );
            
        }
        // at this point the number id odd so print and increment so in the next iteration even is signaled
        // Some error checking would be nice may be an even driven or thread driven syslog bases logger?
        printf("ODD:  %10d\n", currentNumber++);
        pthread_mutex_unlock( &data_mutex );
    }
    
}

int main(char *argv[], int argc)
{
    int even = 0;
    pthread_t even_thread;

    // Weonly need to create one thread as the other thread that is going to ping-pong can run i the context
    // of the main thread.
    if(pthread_create(&even_thread, NULL, print_even, &even)) 
    {
        
        fprintf(stderr, "Error creating even printing thread\n");
        return -1;
    
    }

    // Odd number printing thread sun in the context of main program.
    print_odd();    

    pthread_exit(NULL);

    return 0;
}