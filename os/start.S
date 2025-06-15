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

    # At the end of start_kernel, schedule() will call MRET to switch
	# to the first task, so we parepare the mstatus here.
	# Notice: It is best not to assume that the initial value of mstatus is
	# zero.
	# Set mstatus.MPP to 3, so we still run in Machine mode after MRET.
	# Set mstatus.MPIE to 1, so MRET will enable the interrupt.
    li t0, 3 << 11 | 1 << 7
    csrs mstatus, t0

    j start_kernel

park:
    wfi
    j park

# 在riscv调用规范中，栈指针sp始终是16byte对齐
.balign 16
stacks:
    .skip STACK_SIZE * MAXNUM_CPU

.end