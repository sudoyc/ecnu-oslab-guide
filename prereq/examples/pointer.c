// 指针与结构体：地址本身也是一个值，可以存起来、传给函数
#include <stdio.h>

struct lock {
    int locked;
    const char *name;
};

// 传进来的是地址，所以函数能改到调用者的变量
void add_one(int *p)
{
    *p = *p + 1;
}

void take(struct lock *lk)
{
    lk->locked = 1;   // 等价于 (*lk).locked = 1
}

int main(void)
{
    int n = 10;
    int *p = &n;                 // p 存的是 n 的地址
    printf("n=%d, p=%p, *p=%d\n", n, (void *)p, *p);

    add_one(&n);
    printf("add_one 之后 n=%d\n", n);

    struct lock lk = { 0, "print" };
    take(&lk);
    printf("锁 %s 的 locked=%d\n", lk.name, lk.locked);

    int arr[3] = { 7, 8, 9 };
    int *q = arr;                // 数组名就是首元素地址
    printf("q[1]=%d, *(q+1)=%d\n", q[1], *(q + 1));
    printf("q=%p, q+1=%p（相差 sizeof(int)=%zu）\n", (void *)q, (void *)(q + 1), sizeof(int));
    return 0;
}
