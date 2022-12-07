#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int n;
int total_count;

int isPrime(int n) {
    for(int i = 2; i <= n/2; i++) {
        if(n % i == 0) return 0;
    }
    return 1;
}

void *func1(void *arg) {
    int local_count = 0;
    int* ctr;
    for(int i = 2; i < n/2; i++) {
        if(isPrime(i)) local_count++;
    }
    printf("thrd1 is done.\n");
    ctr = (int *)malloc(sizeof(int));
    *ctr = local_count;
    printf("%d\n", *ctr);
    return ctr;
}

void *func2(void *arg) {
    int local_count = 0;
    int* ctr;
    for(int i = n/2 + 1; i <= n; i++) {
        if(isPrime(i)) local_count++;
    }
    printf("thrd2 is done.\n");
    ctr = (int *)malloc(sizeof(int));
    *ctr = local_count;
    printf("%d\n", *ctr);
    return ctr;
}

int main() {
    pthread_t thrd1, thrd2;
    int* status;
    printf("Enter an integer >= 2 : ");
    scanf("%d", &n);
    

    pthread_create(&thrd1, NULL, func1, NULL);
    pthread_create(&thrd2, NULL, func2, NULL);

    pthread_join(thrd1, &status);
    printf("status %d\n", *status);
    total_count += *status;
    pthread_join(thrd2, &status);
    printf("status %d\n", *status);
    total_count += *status;
    printf("The number of prime numbers: %d\n", total_count);
}