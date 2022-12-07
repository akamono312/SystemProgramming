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

struct PrimeTestRange{
    int startN;
    int endN;
};

pthread_mutex_t total_lock;

void *func(void *arg) {
    int local_count = 0;
    struct PrimeTestRange range;
    range = *(struct PrimeTestRange *)arg;

    for(int i = range.startN; i <= range.endN; i++) {
        if(isPrime(i)) {
            pthread_mutex_lock(&total_lock);
            total_count++;
            pthread_mutex_unlock(&total_lock);
        }
    }
    printf("Thread is done\n");
}


int main() {
    pthread_t thrd1, thrd2;
    int status;
    struct PrimeTestRange r1, r2;
    printf("Enter an integer >= 2 : ");
    scanf("%d", &n);
    r1.startN = 2;
    r1.endN = n/2;
    r2.startN = n/2 + 1;
    r2.endN = n;

    pthread_create(&thrd1, NULL, func, &r1);
    pthread_create(&thrd2, NULL, func, &r2);

    pthread_join(thrd1, &status);
    pthread_join(thrd2, &status);
    printf("The number of prime numbers: %d\n", total_count);
}