#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#define SYS_kern_2D_memcpy 451
int main()
{
    float MAT1[4][4]={{1.0,2.0,3.0,4.0},{3.0,4.0,5.0,6.0},{5.0,6.0,7.0,8.0},{7.0,8.0,9.0,10.0}};
    float MAT2[4][4]={{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0}};
    printf("The initial matrix is:\n");
    int a=0;
    while(a<4)
    {
        int b=0;
        while(b<4)
        {
            printf("%lf ",MAT1[a][b]);
            b++;
        }
        printf("\n");
        a++;
    }
    printf("\n");
    printf("The initial matrix2 is:\n");
    int i=0;
    while(i<4)
    {
        int j=0;
        while(j<4)
        {
            printf("%lf ",MAT2[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
    printf("\n");
    int res= syscall(SYS_kern_2D_memcpy, MAT1, MAT2, 4);
    if(res<0)
    {
        printf("ERROR! Could not perform system call.");
        exit(1);
    }
    printf("The final matrix1 is:\n");
    int e=0;
    while(e<4)
    {
        int f=0;
        while(f<4)
        {
            printf("%lf ",MAT1[e][f]);
            f++;
        }
        printf("\n");
        e++;
    }
    printf("\n");
    printf("The final matrix2 is:\n");
    int g=0;
    while(g<4)
    {
        int p=0;
        while(p<4)
        {
            printf("%lf ",MAT2[g][p]);
            p++;
        }
        printf("\n");
        g++;
    }
    printf("\n");
    return 0;
}
