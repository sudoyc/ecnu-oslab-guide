// Lab1 练习 2：参考答案
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
    va_list ap;
    va_start(ap, fmt); // ap 指向 fmt 后面的第一个可变参数

    for (int i = 0; fmt[i] != '\0'; i++) {
        char c = fmt[i];
        if (c != '%') {
            kputc(c);
            continue;
        }

        c = fmt[++i];
        if (c == '\0') // 格式串以单个 % 结尾：直接结束
            break;

        switch (c) {
        case 'd':
            printint(va_arg(ap, int), 10, 1);
            break;
        case 'p':
            printint(va_arg(ap, int), 16, 0);
            break;
        case 'x':
            printptr(va_arg(ap, unsigned long long));
            break;
        case 'c':
            kputc(va_arg(ap, int)); // char 传参时会被提升成 int
            break;
        case 's': {
            const char *s = va_arg(ap, const char *);
            if (s == 0)
                s = "(null)";
            while (*s)
                kputc(*s++);
            break;
        }
        case '%':
            kputc('%');
            break;
        default: // 不认识的格式：原样输出，方便发现写错的地方
            kputc('%');
            kputc(c);
            break;
        }
    }

    va_end(ap);
}
