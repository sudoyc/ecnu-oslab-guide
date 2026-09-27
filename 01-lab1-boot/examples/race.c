// Lab1 示例：在本机用两个线程重现课程 4.1 的“并行加法”
// 编译：gcc -O1 -pthread race.c -o race
// 运行：./race none     不加锁，结果通常小于 2000000
//       ./race fine     每次 ++ 都加锁（细粒度）
//       ./race coarse   整个循环加一次锁（粗粒度）
//
// 两个线程就相当于内核里的 cpu 0 和 cpu 1。
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define N 1000000

static volatile int sum = 0;
static volatile int started = 0;
static const char *mode = "none";

// ---- 一个最小的自旋锁，和内核里的写法一致 ----
static volatile int locked = 0;

static void lock(void)
{
    // 原子地“写入 1 并返回旧值”。旧值为 0 说明抢到了锁。
    // 在 RISC-V 上这一句会编译成 amoswap.w.aq
    while (__sync_lock_test_and_set(&locked, 1) != 0)
        ;
    __sync_synchronize(); // 内存屏障：临界区的读写不能被挪到加锁之前
}

static void unlock(void)
{
    __sync_synchronize(); // 内存屏障：临界区的读写不能被挪到解锁之后
    __sync_lock_release(&locked); // 原子地写回 0
}
// ------------------------------------------------

static void *worker(void *arg)
{
    int id = (int)(long)arg;

    if (id == 0) {
        __sync_synchronize();
        started = 1;
    } else {
        while (started == 0)
            ;
        __sync_synchronize();
    }

    if (strcmp(mode, "coarse") == 0) {
        lock();
        for (int i = 0; i < N; i++)
            sum++;
        unlock();
    } else if (strcmp(mode, "fine") == 0) {
        for (int i = 0; i < N; i++) {
            lock();
            sum++;
            unlock();
        }
    } else {
        for (int i = 0; i < N; i++)
            sum++;
    }

    printf("cpu %d report: sum = %d\n", id, sum);
    return NULL;
}

int main(int argc, char **argv)
{
    if (argc > 1)
        mode = argv[1];

    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);

    pthread_t th[2];
    for (long i = 0; i < 2; i++)
        pthread_create(&th[i], NULL, worker, (void *)i);
    for (int i = 0; i < 2; i++)
        pthread_join(th[i], NULL);

    clock_gettime(CLOCK_MONOTONIC, &t1);
    double ms = (t1.tv_sec - t0.tv_sec) * 1e3 + (t1.tv_nsec - t0.tv_nsec) / 1e6;
    printf("mode=%s final sum=%d (期望 %d)，耗时 %.1f ms\n", mode, sum, 2 * N, ms);
    return 0;
}
