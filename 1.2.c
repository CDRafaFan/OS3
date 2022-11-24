#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <string.h>
#include <sched.h>
#include <sys/types.h>
#define billion 1000000000.0;
int main()
{
    pid_t pid1,pid2,pid3;
    struct timespec one,two;
    clock_gettime(CLOCK_REALTIME, &one);
    int test=fork();
    if(test==-1)
    {
        printf("Error occured");
    }
    else
    if(test==0)
    {
        struct sched_param var;
        var.sched_priority=0;
        sched_setscheduler(0,SCHED_OTHER,&var);
        execl("/bin/bash","sh","process.sh",NULL);
    }
    else
    {
        struct timespec pop1,pop2;
        clock_gettime(CLOCK_REALTIME, &pop1);
        int again=fork();
        if(again==-1)
        {
            printf("Error occured");
        }
        else
        if(again==0)
        {
            struct sched_param var2;
            var2.sched_priority=10;
            sched_setscheduler(0,SCHED_RR,&var2);
            execl("/bin/bash","sh","process.sh",NULL);
        }
        else
        {
            struct timespec gov,har;
            clock_gettime(CLOCK_REALTIME, &gov);
            int last=fork();
            if(last==-1)
            {
                printf("Error occured");
            }
            else
            if(last==0)
            {
                struct sched_param var3;
                var3.sched_priority=10;
                sched_setscheduler(0,SCHED_FIFO,&var3);
                execl("/bin/bash","sh","process.sh",NULL);
            }
            else
            {
                wait(NULL);
                clock_gettime(CLOCK_REALTIME, &har);
                double timec;
                timec=(har.tv_sec-gov.tv_sec)*billion;
                timec+=(har.tv_nsec-gov.tv_nsec);
                timec/=billion;
                printf("Time taken by process C %lf",timec);
                 wait(NULL);
                clock_gettime(CLOCK_REALTIME, &pop2);
                double timeb;
                timeb=(pop2.tv_sec-pop1.tv_sec)*billion;
                timeb+=(pop2.tv_nsec-pop1.tv_nsec);
                timeb/=billion;
                printf("Time taken by process B %lf",timeb);
                wait(NULL);
                clock_gettime(CLOCK_REALTIME, &two);
                double timea;
                timea=(two.tv_sec-one.tv_sec)*billion;
                timea+=(two.tv_nsec-one.tv_nsec);
                timea/=billion;
                printf("Time taken by process A %lf",timea);
            }
        }
    }
    return 0;
}
