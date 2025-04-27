# Branch 跳转指令
#
# 指令：bne, beq, blt, bltu, bgeu
# 伪指令：ble, bleu, bgt, bgtu
#        beqz, bnez, bltz, blez, bgtz, bgez
#
# FORMAT
#   branch rs, rd, immd
#   比较rd，rs，如果条件成立，跳到PC + immd*2 的地址
#   immd ∈ [-4096, 4094]
#   bxxz等指令，rd=0，和0比较

.text
.globl _start

_start:
    li x5, 0
    li x6, 5
loop:
    addi x5, x5, 1
    blt x5, x6, loop

stop:
    j stop

.end                                # end of file
