// 用 RISC-V 交叉编译器编译，对照 C 看每条汇编
int sum(int *a, int n)
{
    int s = 0;
    for (int i = 0; i < n; i++)
        s += a[i];
    return s;
}

int twice(int x)
{
    return x * 2 + 1;
}
