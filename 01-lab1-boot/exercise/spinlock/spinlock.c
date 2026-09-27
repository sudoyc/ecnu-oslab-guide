// Lab1 练习 3：自旋锁。写法和内核 src/kernel/lock/spinlock.c 完全一致
// 编译运行：make
#include "spinlock.h"

void spinlock_init(spinlock_t *lk, char *name)
{
    // TODO：初始化三个字段。cpuid 用 -1 表示“没有人持有”
    (void)lk;
    (void)name;
}

int spinlock_holding(spinlock_t *lk)
{
    // TODO：锁被锁上，并且持有者是当前 CPU
    (void)lk;
    return 0;
}

void spinlock_acquire(spinlock_t *lk)
{
    // TODO：
    // 1. push_off() 关中断（为什么要先关？看讲义“死锁的第二种来源”）
    // 2. 如果当前 CPU 已经持有这把锁，panic（重复上锁会永远等下去）
    // 3. 用 __sync_lock_test_and_set(&lk->locked, 1) 原子地抢锁，抢不到就一直转
    // 4. __sync_synchronize() 内存屏障
    // 5. 记录持有者
    (void)lk;
}

void spinlock_release(spinlock_t *lk)
{
    // TODO：顺序和 acquire 相反
    // 1. 如果当前 CPU 没有持有这把锁，panic
    // 2. 清除持有者
    // 3. __sync_synchronize()
    // 4. __sync_lock_release(&lk->locked)
    // 5. pop_off()
    (void)lk;
}
