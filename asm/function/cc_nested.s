# Calling Convention
# 嵌套调用
# void _start()
# {
#     // calling nested routine
#     aa_bb(3, 4);
# }
#
# int aa_bb(int a, int b)
# {
#     return square(a) + square(b);
# }
#
# int square(int num)
# {
#     return num * num;
# }


.text
.globl _start

_start:
    la sp, stack_end

    li a0, 3
    li a1, 4
    call aa_bb

stop:
    j stop

aa_bb:
    addi sp, sp, -12
    sw s0, 0(sp)
    sw s1, 4(sp)
    sw ra, 8(sp)        # 接着要调用square会覆盖ra，所以需要压栈

    call square

    mv s0, a0
    mv a0, a1
    call square

    add s0, s0, a0
    mv a0, s0

    lw s0, 0(sp)
    lw s1, 4(sp)
    lw ra, 8(sp)
    addi sp, sp, 12

    ret

square:
    # prologue
    addi sp, sp, -8
    sw s0, 0(sp)
    sw s1, 4(sp)

    mv s0, a0
    mul s1, s0, s0
    mv a0, s1

    # epilogue
    lw s0, 0(sp)
    lw s1, 4(sp)
    addi sp, sp, 8

    ret

stack_start:
    .rept 12
    .word 0
    .endr
stack_end:

.end                                # end of file
