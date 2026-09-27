// Lab1 练习 2：先在本机写出 printf，测试通过后再搬进内核的 print.c
// 编译运行：make   （等价于 gcc -Wall -Wextra kprintf.c test.c -o test && ./test）
//
// 规则和课程框架 src/kernel/lib/print.c 的注释保持一致：
//   %d  32 位有符号数，十进制
//   %p  32 位无符号数，十六进制，不带前缀（注意：和标准 C 的 %p 不同）
//   %x  64 位无符号数，带 0x 前缀，固定 16 位十六进制（和标准 C 的 %x 也不同）
//   %c  单个字符
//   %s  字符串，传入 NULL 时输出 (null)
//   %%  输出一个 %
// 遇到不认识的格式（例如 %q）：原样输出 %q
#include <stdarg.h>
#include "kprintf.h"

static char digits[] = "0123456789abcdef";

// 和框架里的 printint 一模一样，只是把 uart_putc_sync 换成了 kputc
static void printint(int xx, int base, int sign)
{
    char buf[16];
    int i;
    unsigned int x;

    if (sign && (sign = xx < 0))
        x = -xx;
    else
        x = xx;

    i = 0;
    do {
        buf[i++] = digits[x % base];
    } while ((x /= base) != 0);

    if (sign)
        buf[i++] = '-';

    while (--i >= 0)
        kputc(buf[i]);
}

// 和框架里的 printptr 一模一样
static void printptr(unsigned long long x)
{
    kputc('0');
    kputc('x');
    for (int i = 0; i < (int)(sizeof(unsigned long long) * 2); i++, x <<= 4)
        kputc(digits[x >> (sizeof(unsigned long long) * 8 - 4)]);
}

void kprintf(const char *fmt, ...)
{
    // TODO：用 va_list / va_start / va_arg / va_end 实现
    // 思路：逐个字符扫描 fmt，普通字符直接 kputc；
    //       遇到 '%' 就看下一个字符，决定从 va_list 里取什么类型的参数。
    (void)fmt;
    (void)printint;
    (void)printptr;
}
