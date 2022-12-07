#include <stdio.h>
#include <pthread.h>

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
    for(int i = 2; i < n/2; i++) {
        if(isPrime(i)) local_count++;
    }
    total_count += local_count;
}

void *func2(void *arg) {
    int local_count = 0;
    for(int i = n/2 + 1; i <= n; i++) {
        if(isPrime(i)) local_count++;
    }
    total_count += local_count;
}

int main() {
    pthread_t thrd1, thrd2;
    int status;
    printf("Enter an integer >= 2 : ");
    scanf("%d", &n);
    

    pthread_create(&thrd1, NULL, func1, NULL);
    pthread_create(&thrd2, NULL, func2, NULL);

    pthread_join(thrd1, &status);
    pthread_join(thrd2, &status);
    printf("The number of prime numbers: %d\n", total_count);
}