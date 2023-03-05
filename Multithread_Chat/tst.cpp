#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define num_thread 10


void *runner(void *data); /* threads call this function */
int main(int argc, char *argv[])
{
    pthread_t tid[num_thread]; /* the thread identifier */
    pthread_attr_t attr; /* set of thread attributes */
    /* set the default attributes of the thread */
    pthread_attr_init(&attr);
    /* create the thread */
    for(int i=0; i<num_thread;i++)
        pthread_create(&tid[i], &attr, runner,(void*)&i);
    /* wait for the thread to exit */
    for(int i=0; i<num_thread;i++)
        pthread_join(tid[i],NULL);
}
    /* The thread will execute in this function */

void *runner(void* data)
{
    printf("Hello This is Thread No %d\n", *((int*)data));
    pthread_exit(0);
}
