#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <pthread.h>
#include <unistd.h>

void *countA(void *arg)
{
    const struct sched_param para = {.sched_priority = 0};
    pthread_t tself = pthread_self();
    int ret = pthread_setschedparam(tself, SCHED_OTHER, &para);

    if (ret >0)
    {
        printf("sone error in A");
    }
    long before = clock();
    for (int i = 1; i < INT_MAX ; i++)
    {
    }
    for (int i = 1; i < INT_MAX; i++)
    {
    }
    long after =clock();
    double elapsed=(double)(after - before) / CLOCKS_PER_SEC;
    printf("%lf seconds elapsed in count A \n", elapsed);
}
void *countB(void *arg)
{
    struct sched_param para2 = {.sched_priority = 20};
    pthread_t tself = pthread_self();
    int ret = pthread_setschedparam(tself, SCHED_RR, &para2) ;

    if (ret >0)
    {
        printf("sone error in B");
    }
    long before = clock();
    for (int i = 1; i < INT_MAX ; i++)
    {
    }
    for (int i = 1; i < INT_MAX; i++)
    {
    }
    long after =clock();
    double elapsed=(double)(after - before) / CLOCKS_PER_SEC;
    printf("%lf seconds elapsed in count B \n", elapsed);
}
void *countC(void *arg)
{
    const struct sched_param para3 = {.sched_priority = 20};
    pthread_t tself = pthread_self();
    int ret = pthread_setschedparam(tself, SCHED_FIFO, &para3);

    if (ret >0)
    {
        printf("sone error in C");
    }
    long before = clock();
    for (int i = 1; i < INT_MAX ; i++)
    {
    }
    for (int i = 1; i < INT_MAX; i++)
    {
    }
    long after =clock();
    double elapsed=(double)(after - before) / CLOCKS_PER_SEC;
    printf("%lf seconds elapsed in count C \n", elapsed);
}
void main(){

    pthread_t th1 ;
    pthread_t th2 ;
    pthread_t th3 ;
    //printf("Works fine ig \n");
    pthread_create(&th1, NULL, countA,NULL);
    pthread_create(&th2, NULL, countB, NULL);
    pthread_create(&th3, NULL, countC, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    pthread_join(th3, NULL) ;

    //     counta();

    //printf("%lf seconds elapsed \n", elapsed);
}
