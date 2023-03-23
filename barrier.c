#include "barrier.h"

void func1() {
    int tid = pthread_self();
    printf("Func 1: %d\n", tid%1000);
}

void func2() {
    int tid = pthread_self();
    printf("Func 2: %d\n", tid%1000);
}

void func3() {
    int tid = pthread_self();
    printf("Func 3: %d\n", tid%1000);
}

void barrier_tester() {
    func1();
    barrier_wait();
    func2();
    barrier_wait();
    func3();
    barrier_wait();
}

void no_barrier_tester() {
    func1();
    func2();
    func3();
}

void run(pthread_t* threads, void (*btest) ()) {
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, btest, NULL);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
       pthread_join(threads[i], NULL);
    }
}

int main() {
    pthread_t threads[NUM_THREADS];
    printf("\n----- NO BARRIER -----\n");
    run(threads, &no_barrier_tester);
    printf("\n----- WITH BARRIER -----\n");
    barrier_init();
    run(threads, &barrier_tester);
    exit(0);
}