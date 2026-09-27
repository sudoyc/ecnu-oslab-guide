// 自旋锁测试：两个线程各加 N 次，结果必须正好是 2N
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "spinlock.h"

#define N 1000000

static __thread int my_id;
static __thread int noff;
int mycpuid(void) { return my_id; }
void push_off(void) { noff++; }
void pop_off(void)
{
    if (noff < 1)
        panic("pop_off 比 push_off 多");
    noff--;
}
void panic(const char *s)
{
    printf("panic! %s\n", s);
    exit(1);
}

static spinlock_t lk;
static volatile int sum;

static void *worker(void *arg)
{
    my_id = (int)(long)arg;
    for (int i = 0; i < N; i++) {
        spinlock_acquire(&lk);
        if (!spinlock_holding(&lk))
            panic("acquire 之后 holding 应该为真");
        sum++;
        spinlock_release(&lk);
    }
    if (noff != 0)
        panic("push_off / pop_off 没有配对");
    return NULL;
}

int main(void)
{
    spinlock_init(&lk, "test");
    my_id = 9;
    if (spinlock_holding(&lk))
        panic("刚初始化的锁不应该被持有");

    pthread_t t[2];
    for (long i = 0; i < 2; i++)
        pthread_create(&t[i], NULL, worker, (void *)i);
    for (int i = 0; i < 2; i++)
        pthread_join(t[i], NULL);

    printf("sum = %d (期望 %d) %s\n", sum, 2 * N, sum == 2 * N ? "PASS" : "FAIL");
    return sum != 2 * N;
}
