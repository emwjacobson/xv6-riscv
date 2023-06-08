#include "thread.h"
#include "user.h"
#include "kernel/riscv.h"

int thread_create(void *(startup_routine)(void*), void *arg) {
    // Allocate user stack of PGSIZE bytes
    void *stack = malloc(PGSIZE);

    // Call clone() to create child
    int ret = clone(stack);

    if (ret == -1) { // Parent failed to clone. Child doesn't exist
        return -1;
    } else if (ret == 0) { // Child
        // printf("Child: %d\n", ret);
        startup_routine(arg);
        free(stack);
        exit(0);
    } else { // Parent
        // printf("Parent: %d\n", ret);
        return 0;
    }
    return ret;
}

// https://gcc.gnu.org/onlinedocs/gcc-4.1.0/gcc/Atomic-Builtins.html

void lock_init(struct lock_t* lock) {
    lock->locked = 0;
}

void lock_acquire(struct lock_t* lock) {
    while (__sync_lock_test_and_set(&(lock->locked), 1)) {}
}

void lock_release(struct lock_t* lock) {
    __sync_lock_release(&(lock->locked));
}
