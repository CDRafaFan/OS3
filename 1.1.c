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
    struct timespec one,two;
    clock_gettime(CLOCK_REALTIME,&one);
    long long int a=0;
    for(long long int i=0;i<4294967296;i++)
    {
        a++;
    }
    clock_gettime(CLOCK_REALTIME,&two);
    double timea = (((two.tv_sec - one.tv_sec) * 1000000000) +(two.tv_nsec - one.tv_nsec))/1000000000.0;
    printf("Time taken by countA() %lf\n",timea);
    return NULL;
}
void* countB()
{
    struct timespec three,four;
    clock_gettime(CLOCK_REALTIME,&three);
    long long int b=0;
    for(long long int n=0;n<4294967296;n++)
    {
        b++;
    }
    clock_gettime(CLOCK_REALTIME,&four);
    double timeb = (((four.tv_sec - three.tv_sec) * 1000000000) +(four.tv_nsec - three.tv_nsec))/1000000000.0;
    printf("Time taken by countB() %lf\n",timeb);
    return NULL;
}
void* countC()
{   
    struct timespec five,six;
    clock_gettime(CLOCK_REALTIME,&five);
    long long int c=0;
    for(long long int f=0;f<4294967296;f++)
    {
        c++;
    }
    clock_gettime(CLOCK_REALTIME,&six);
    double timec = (((six.tv_sec - five.tv_sec) * 1000000000) +(six.tv_nsec - five.tv_nsec))/1000000000.0;
    printf("Time taken by countC() %lf\n",timec);
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
    pri2.sched_priority=20;
    pthread_setschedparam(t2,SCHED_RR,&pri2);
    
    struct sched_param pri3;
    pri3.sched_priority=30;
    pthread_setschedparam(t3,SCHED_FIFO,&pri3);


    pthread_join(t1,NULL);

    pthread_join(t2,NULL);
 
    pthread_join(t3,NULL);
  
    return 0;
}
