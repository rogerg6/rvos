# 汇编调用c语言函数

.text
.globl _start
.globl calc

_start:
    la sp, stack_end

    li a0, 1                        # x6 = 1
    li a1, 2                        # x7 = 2
    call calc

stop:
    j stop

stack_start:
    .rept 12
    .word 0
    .endr
stack_end:

.end                                # end of file
