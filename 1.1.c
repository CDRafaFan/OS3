#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <libgen.h>
#include <pthread.h>
#include <math.h>
void* countA()
{
    long long int counter=pow(2,32);
    struct timespec one,two;
    clock_gettime(CLOCK_REALTIME,&one);
    for(long long int i=1;i<counter;i++)
    {
        //printf("Hello world");
    }
    clock_gettime(CLOCK_REALTIME,&two);
    double timea = (((two.tv_sec - one.tv_sec) * 1000000000) +(two.tv_nsec - one.tv_nsec));
    printf("Time taken by countA() %lf\n",timea/1000000000.0);
    return NULL;
}
void* countB()
{
    long long int counter=pow(2,32);
    struct timespec one,two;
    clock_gettime(CLOCK_REALTIME,&one);
    for(long long int i=1;i<counter;i++)
    {
        //printf("Hello world");
    }
    clock_gettime(CLOCK_REALTIME,&two);
    double timea = (((two.tv_sec - one.tv_sec) * 1000000000) +(two.tv_nsec - one.tv_nsec));
    printf("Time taken by countB() %lf\n",timea/1000000000.0);
    return NULL;
}
void* countC()
{
    long long int counter=pow(2,32);
    struct timespec one,two;
    clock_gettime(CLOCK_REALTIME,&one);
    for(long long int i=1;i<counter;i++)
    {
        //printf("Hello world");
    }
    clock_gettime(CLOCK_REALTIME,&two);
    double timea = (((two.tv_sec - one.tv_sec) * 1000000000) +(two.tv_nsec - one.tv_nsec));
    printf("Time taken by countC() %lf\n",timea/1000000000.0);
    return NULL;
}
int main()
{
    pthread_t t1,t2,t3;
    pthread_create(&t1,NULL,&countA,NULL);
    pthread_create(&t2,NULL,&countB,NULL);
    pthread_create(&t3,NULL,&countC,NULL);
    struct sched_param pri;
    pri.sched_priority=0;
    pthread_setschedparam(t1,SCHED_OTHER,&pri);
    struct sched_param pri2;
    pri.sched_priority=20;
    pthread_setschedparam(t2,SCHED_RR,&pri2);
    struct sched_param pri3;
    pri.sched_priority=30;
    pthread_setschedparam(t3,SCHED_FIFO,&pri3);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    return 0;
}
