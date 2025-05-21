#include "platform.h"

# 每个hart栈大小=1K
.equ STACK_SIZE, 1024
.globl _start
.text

_start:
    csrr t0, mhartid        # read hart ID
    mv tp, t0
    bnez t0, park           # jump to park if not hart0

    # setup stack of each hart
    slli t0, t0, 10                     # t0 = hartID * 1024
    la sp, stacks + STACK_SIZE
    add sp, sp, t0

    j start_kernel

park:
    wfi
    j park

# 在riscv调用规范中，栈指针sp始终是16byte对齐
.balign 16
stacks:
    .skip STACK_SIZE * MAXNUM_CPU

.end