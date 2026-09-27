// 位运算：只改某几位，其他位不动
#include <stdio.h>

void show(const char *what, unsigned x)
{
    printf("%-24s", what);
    for (int i = 15; i >= 0; i--)
        putchar((x >> i) & 1 ? '1' : '0');
    printf("  (0x%04x)\n", x);
}

int main(void)
{
    unsigned x = 0x1234;
    show("x", x);
    show("1 << 11", 1u << 11);
    show("mask = 3 << 11", 3u << 11);
    show("x | (1<<3)   set", x | (1u << 3));
    show("x & ~(1<<2)  clear", x & ~(1u << 2));
    show("x & mask", x & (3u << 11));
    show("(x>>11) & 3", (x >> 11) & 3);

    unsigned mask = 3u << 11;
    unsigned y = (x & ~mask) | (1u << 11);   // 第11-12位改成 01
    show("(x & ~mask) | (1<<11)", y);
    return 0;
}
