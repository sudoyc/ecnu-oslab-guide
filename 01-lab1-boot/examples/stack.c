// Lab1 示例：观察函数调用如何使用栈和 ra 寄存器
// riscv64-elf-gcc -O1 -c stack.c -o stack.o
// riscv64-elf-objdump -d stack.o

__attribute__((noinline)) int leaf(int x) // 叶子函数：不再调用别人，往往不需要栈
{
    return x * 2 + 1;
}

int caller(int x)          // 非叶子函数：要调用 leaf，必须先把 ra 存到栈上
{
    int local[4];
    for (int i = 0; i < 4; i++)
        local[i] = leaf(x + i);
    return local[0] + local[3];
}
