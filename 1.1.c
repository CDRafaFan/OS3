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
    long long int counter=pow(2,32);long long int a=0;
    for(long long int i=1;i<counter;i++)
    {
        a++;
    }
    return NULL;
}
void* countB()
{
    long long int counter=pow(2,32);long long int b=0;
    for(long long int n=1;n<counter;n++)
    {
        b++;
    }
    return NULL;
}
void* countC()
{
    long long int counter=pow(2,32);long long int c=0;
    for(long long int u=1;u<counter;u++)
    {
        c++;
    }
    return NULL;
}
int main()
{
    pthread_t t1,t2,t3;
    struct timespec one,two;
    clock_gettime(CLOCK_REALTIME,&one);
    pthread_create(&t1,NULL,&countA,NULL);
    struct timespec three,four;
    clock_gettime(CLOCK_REALTIME,&three);
    pthread_create(&t2,NULL,&countB,NULL);
    struct timespec five,six;
    clock_gettime(CLOCK_REALTIME,&five);
    pthread_create(&t3,NULL,&countC,NULL);
    struct sched_param pri;
    pri.sched_priority=0;
    pthread_setschedparam(t1,SCHED_OTHER,&pri);
    struct sched_param pri2;
    pri2.sched_priority=20;
    pthread_setschedparam(t2,SCHED_RR,&pri2);
    struct sched_param pri3;
    pri3.sched_priority=30;
    pthread_setschedparam(t3,SCHED_FIFO,&pri3);
    pthread_join(t1,NULL);
    clock_gettime(CLOCK_REALTIME,&two);
    double timea = (((two.tv_sec - one.tv_sec) * 1000000000) +(two.tv_nsec - one.tv_nsec));
    printf("Time taken by countA() %lf\n",timea/1000000000.0);
    pthread_join(t2,NULL);
    clock_gettime(CLOCK_REALTIME,&four);
    double timeb = (((four.tv_sec - three.tv_sec) * 1000000000) +(four.tv_nsec - three.tv_nsec));
    printf("Time taken by countB() %lf\n",timeb/1000000000.0);
    pthread_join(t3,NULL);
    clock_gettime(CLOCK_REALTIME,&six);
    double timec = (((six.tv_sec - five.tv_sec) * 1000000000) +(six.tv_nsec - five.tv_nsec));
    printf("Time taken by countC() %lf\n",timec/1000000000.0);
    return 0;
}
