#include <stdio.h>
#include <pthread.h>

int isPrime(int n) {
    for(int i = 2; i <= n/2; i++) {
        if(n % i == 0) return 0;
    }
    return 1;
}


int main() {
    int n;
    int count = 0;
    printf("Enter an integer >= 2 : ");
    scanf("%d", &n);
    for(int i = 2; i <= n; i++) {
        if(isPrime(i)) count++;
    }
    printf("The number of prime numbers: %d\n", count);
}