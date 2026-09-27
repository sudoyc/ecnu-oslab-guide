// kprintf 的测试：kputc 把字符写进缓冲区，再和期望值比较
#include <stdio.h>
#include <string.h>
#include "kprintf.h"

static char out[256];
static int len;

void kputc(int c)
{
    if (len < (int)sizeof(out) - 1)
        out[len++] = (char)c;
}

static int failed;

#define EXPECT(want, ...)                                              \
    do {                                                               \
        len = 0;                                                       \
        kprintf(__VA_ARGS__);                                          \
        out[len] = '\0';                                               \
        if (strcmp(out, want) == 0) {                                  \
            printf("PASS  %-28s -> \"%s\"\n", #__VA_ARGS__, out);      \
        } else {                                                       \
            printf("FAIL  %-28s -> \"%s\", want \"%s\"\n",             \
                   #__VA_ARGS__, out, want);                           \
            failed++;                                                  \
        }                                                              \
    } while (0)

int main(void)
{
    EXPECT("hello", "hello");
    EXPECT("cpu 0 is booting!\n", "cpu %d is booting!\n", 0);
    EXPECT("-123 45", "%d %d", -123, 45);
    EXPECT("-2147483648", "%d", -2147483647 - 1);
    EXPECT("ff", "%p", 255);
    EXPECT("0x0000000080000000", "%x", 0x80000000ULL);
    EXPECT("A", "%c", 'A');
    EXPECT("[os]", "[%s]", "os");
    EXPECT("(null)", "%s", (char *)0);
    EXPECT("100%", "100%%");
    EXPECT("%q", "%q");
    EXPECT("a=1,b=x,c=hi", "a=%d,b=%c,c=%s", 1, 'x', "hi");

    printf(failed ? "\n%d 个用例失败\n" : "\n全部通过\n", failed);
    return failed != 0;
}
