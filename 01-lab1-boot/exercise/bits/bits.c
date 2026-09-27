// Lab1 练习 1：位运算。内核里改寄存器的某几位全靠它。
// 编译运行：make   （等价于 gcc -Wall bits.c -o bits && ./bits）
// 把 TODO 补完，直到输出全部是 PASS。
#include <stdio.h>
#include <stdint.h>

#define MPP_MASK (3UL << 11)   // mstatus 的 MPP 字段占第 11、12 两位
#define MPP_S    (1UL << 11)   // 值 01 表示 S-mode
#define MPP_M    (3UL << 11)   // 值 11 表示 M-mode

// TODO 1：把 status 的 MPP 字段改成 S-mode，其他位保持不变
static uint64_t set_mpp_s(uint64_t status)
{
    return status; // 改这里
}

// TODO 2：取出 MPP 字段的值（结果应为 0、1 或 3）
static unsigned get_mpp(uint64_t status)
{
    return 0; // 改这里
}

static void check(const char *name, int ok)
{
    printf("%s %s\n", ok ? "PASS" : "FAIL", name);
}

int main(void)
{
    uint64_t s = 0xa00001888UL; // 一个 MPP=M 并带有其他杂位的 mstatus 值
    uint64_t t = set_mpp_s(s);

    check("MPP 变成 S", (t & MPP_MASK) == MPP_S);
    check("其他位不变", (t & ~MPP_MASK) == (s & ~MPP_MASK));
    check("get_mpp(M) == 3", get_mpp(s) == 3);
    check("get_mpp(S) == 1", get_mpp(t) == 1);
    return 0;
}
