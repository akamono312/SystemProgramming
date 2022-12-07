#include <stdio.h>
#include <pthread.h>

void *func(void *arg) {
    for(int i = 0; i < 10; i++) {
        printf("Hello in thread\n");
        sleep(1);
    }
}

void *func2(void *arg) {
    for(int i = 0; i < 10; i++) {
        printf("Hello in thread\n");
        sleep(1);
    }
}

int main() {
    pthread_t thrd1, thrd2;
    int result;
    int status;

    result = pthread_create(&thrd1, NULL, func, NULL);
    result = pthread_create(&thrd2, NULL, func2, NULL);
    for(int i = 0; i < 5; i++) {
        printf("hi in main\n");
        sleep(1);
    }
    pthread_join(thrd1, &status);
    pthread_join(thrd2, &status);
}