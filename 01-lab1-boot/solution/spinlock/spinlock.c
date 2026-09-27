// Lab1 练习 3 参考答案
#include "spinlock.h"

void spinlock_init(spinlock_t *lk, char *name)
{
    lk->locked = 0;
    lk->name = name;
    lk->cpuid = -1;
}

int spinlock_holding(spinlock_t *lk)
{
    return lk->locked && lk->cpuid == mycpuid();
}

void spinlock_acquire(spinlock_t *lk)
{
    push_off(); // 关中断：持锁期间不能被本 CPU 的中断处理程序打断
    if (spinlock_holding(lk))
        panic("spinlock_acquire: 重复上锁");

    // 原子交换：写入 1，返回旧值。旧值为 0 表示抢到了
    while (__sync_lock_test_and_set(&lk->locked, 1) != 0)
        ;
    __sync_synchronize(); // 临界区的访存不能被提前到拿锁之前

    lk->cpuid = mycpuid();
}

void spinlock_release(spinlock_t *lk)
{
    if (!spinlock_holding(lk))
        panic("spinlock_release: 释放了不属于自己的锁");

    lk->cpuid = -1;
    __sync_synchronize(); // 临界区的访存不能被推迟到放锁之后
    __sync_lock_release(&lk->locked);
    pop_off();
}
