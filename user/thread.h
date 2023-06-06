#include "kernel/types.h"

struct lock_t {
    uint locked;
};

int thread_create(void *(startup_routine)(void*), void *arg);
void lock_init(struct lock_t* lock);
void lock_acquire(struct lock_t* lock);
void lock_release(struct lock_t* lock);
