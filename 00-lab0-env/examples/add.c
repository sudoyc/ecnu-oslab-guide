// Lab0 示例：一个不依赖任何库的 C 文件
// 交叉编译（前缀按你的工具链替换）：riscv64-elf-gcc -O1 -c add.c -o add.o
// 查看：    riscv64-elf-objdump -d add.o
//           riscv64-elf-readelf -S add.o

int counter = 42;          // 有初值的全局变量 -> .data
int zeros[16];             // 没有初值的全局变量 -> .bss
const char msg[] = "hi";   // 只读常量 -> .rodata

int add(int a, int b)      // 函数代码 -> .text
{
    return a + b + counter;
}
