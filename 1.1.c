#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <pthread.h>

void *countA() {
  struct timespec start1, end1;
  clock_gettime(CLOCK_REALTIME, &start1);
  nice(0);
  unsigned long int countA = 0;
  for (unsigned long int i = 1; i <= 4294967296; i++) {
    countA++;
  }
  clock_gettime(CLOCK_REALTIME, &end1);
  double timeA = (((end1.tv_sec - start1.tv_sec) * 1000000000) +
                       (end1.tv_nsec - start1.tv_nsec)) /
                      1000000000.0;
  printf("Time taken by ThreadA: %lf \n", timeA);
  return NULL;
}

void *countB() {
  struct timespec start2, end2;
  clock_gettime(CLOCK_REALTIME, &start2);
  unsigned long int countB = 0;
  for (unsigned long int i = 1; i <= 4294967296; i++) {
    countB++;
  }
  clock_gettime(CLOCK_REALTIME, &end2);
  double timeB = (((end2.tv_sec - start2.tv_sec) * 1000000000) +
                       (end2.tv_nsec - start2.tv_nsec)) /
                      1000000000.0;
  printf("Time taken by ThreadB: %lf \n", timeB);
  return NULL;
}

void *countC() {
  struct timespec start3, end3;
  clock_gettime(CLOCK_REALTIME, &start3);
  unsigned long int countC = 0;
  for (unsigned long int i = 1; i <= 4294967296; i++) {
    countC++;
  }
  clock_gettime(CLOCK_REALTIME, &end3);
  double timeC = (((end3.tv_sec - start3.tv_sec) * 1000000000) +
                       (end3.tv_nsec - start3.tv_nsec)) /
                      1000000000.0;
  printf("Time taken by ThreadC: %lf \n", timeC);
  return NULL;
}

int main() {

  pthread_t tid1, tid2, tid3;

  pthread_create(&tid1, NULL, &countA, NULL);
  pthread_create(&tid2, NULL, &countB, NULL);
  pthread_create(&tid3, NULL, &countC, NULL);
  struct sched_param param1;
  param1.sched_priority = 0;
  pthread_setschedparam(tid1, SCHED_OTHER, &param1);
  struct sched_param param2;
  param2.sched_priority = 10;
  pthread_setschedparam(tid2, SCHED_RR, &param2);
  struct sched_param param3;
  param3.sched_priority = 10;
  pthread_setschedparam(tid3, SCHED_FIFO, &param3);
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_join(tid3, NULL);

  return 0;
}
