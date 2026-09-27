#pragma once
// 和课程框架 src/kernel/lock/type.h 里的 spinlock_t 一样
typedef struct spinlock {
    int locked; // 是否上锁
    char *name; // 锁的名字
    int cpuid;  // 持有该锁的 CPU
} spinlock_t;

// 本机模拟：线程 0/1 当作 cpu 0/1。内核里用 mycpuid()
int mycpuid(void);
// 本机模拟：关/开中断在用户态做不了，这里只记录层数，接口和内核一致
void push_off(void);
void pop_off(void);
void panic(const char *s);

void spinlock_init(spinlock_t *lk, char *name);
int spinlock_holding(spinlock_t *lk);
void spinlock_acquire(spinlock_t *lk);
void spinlock_release(spinlock_t *lk);
