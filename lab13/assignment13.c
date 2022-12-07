#include <stdio.h>
#include <pthread.h>
#include <time.h>

int total_cnt, n;
int testNum = 2;
pthread_mutex_t total_cnt_lock;
pthread_mutex_t testNum_lock;

int isPrime(int n) {
    for(int i = 2; i <= n/2; i++) {
        if(n % i == 0) return 0;
    }
    return 1;
}


void* prime_count(void* arg) {
    int num;
    long time;
    double ms;
    struct timespec begin, end;
    int idx = *(int *)arg;

    clock_gettime(CLOCK_REALTIME, &begin);
    while(testNum <= n) {
        pthread_mutex_lock(&testNum_lock);
        num = testNum;
        testNum++;
        pthread_mutex_unlock(&testNum_lock);
        if(isPrime(num)) {
            pthread_mutex_lock(&total_cnt_lock);
            total_cnt++;
            pthread_mutex_unlock(&total_cnt_lock);
        }
    }
    clock_gettime(CLOCK_REALTIME, &end);
    time = (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec);
    ms = (double)time / 1000000;
    printf("Thread%d is done. The time it took to run this thread is %0.3fms.\n", idx, ms);
    
}

int main() {
    pthread_t thrd1, thrd2, thrd3;
    struct timespec begin, end;
    int *status;
    int idx1, idx2, idx3;
    printf("Enter a positive integer: ");
    scanf("%d", &n);

    idx1 = 1; idx2 = 2; idx3 = 3;
    pthread_create(&thrd1, NULL, prime_count, &idx1);
    pthread_create(&thrd2, NULL, prime_count, &idx2);
    pthread_create(&thrd3, NULL, prime_count, &idx3);

    pthread_join(thrd1, (void *)&status);
    pthread_join(thrd2, (void *)&status);
    pthread_join(thrd3, (void *)&status);

    printf("The number of prime numbers: %d\n", total_cnt);
}