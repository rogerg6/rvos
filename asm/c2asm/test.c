
int calc(int a, int b) 
{
    int c;

    // c内嵌汇编
    __asm__ volatile(
        "add %0, %1, %2"
        :"=r"(c)                // 输出参数
        :"r"(a), "r"(b)         // 输入参数
                                // 更改的寄存器列表
    );

    return c;
}