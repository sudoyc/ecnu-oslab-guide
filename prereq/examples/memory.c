// 内存与地址：变量住在哪、十六进制怎么读、sizeof 是多少
#include <stdio.h>

int g = 42;          // 全局变量
char name[4] = "abc"; // 4 个字节：'a' 'b' 'c' '\0'

int main(void)
{
    int x = 255;
    printf("x 的值：十进制 %d，十六进制 0x%x\n", x, x);
    printf("sizeof(char)=%zu  sizeof(int)=%zu  sizeof(long)=%zu\n",
           sizeof(char), sizeof(int), sizeof(long));

    // %p 打印地址（C 标准库的 %p，和课程框架的约定无关）
    printf("g    住在 %p\n", (void *)&g);
    printf("x    住在 %p\n", (void *)&x);
    for (int i = 0; i < 4; i++)
        printf("name[%d] 住在 %p，内容 0x%02x\n", i, (void *)&name[i], name[i]);
    return 0;
}
