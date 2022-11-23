#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <libgen.h>
#include <pthread.h>
#include <math.h>

long long int power(){
    long long int x = 1;
    for(int i=1;i<=32;i++){
        x = x*2;
    }
    return x;
}

double subtract_time(struct timespec start, struct timespec end){
   
    return (((end.tv_sec - start.tv_sec) * 1000000000) +(end.tv_nsec - start.tv_nsec))/1000000000.0;

}

void* countA()
{
    struct timespec one,two;
    clock_gettime(CLOCK_REALTIME,&one);
    nice(0);
    long long int x = power();
    long long int i=0;
    while(i<x)
    {
        i++;
    }
    clock_gettime(CLOCK_REALTIME,&two);
    double timea = subtract_time(one,two);
    printf("Time taken by countA() %lf\n",timea);
    return NULL;
}
void* countB()
{
    struct timespec three,four;
    clock_gettime(CLOCK_REALTIME,&three);
    long long int y = power();
    long long int n=0;
    while(n<y)
    {
        n++;
    }
    clock_gettime(CLOCK_REALTIME,&four);
    double timeb = subtract_time(three,four);
    printf("Time taken by countB() %lf\n",timeb);
    return NULL;
}
void* countC()
{   
    struct timespec five,six;
    clock_gettime(CLOCK_REALTIME,&five);
    long long int f=0;
    long long int z = power();
    while(f<z)
    {
        f++;
    }
    clock_gettime(CLOCK_REALTIME,&six);
    double timec = subtract_time(five,six);
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
