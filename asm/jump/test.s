# 无条件跳转指令
#
# 指令：jal(Jump And Link), jalr(Jump And Link Registe)
# 伪指令：j, jr
#
# FORMAT
#   jal rd, immd             // 用于调用子过程
#   rd存储jal下一条指令地址(即返回地址)，跳转到 PC + immd*2 地址处，
#   immd有20位，所以跳转范围 PC ± 1M
#
#   jalr rd, immd(rs1)       // 用于调用子过程
#   rd存储jalr下一条指令地址(即返回地址)，跳转到 rs1 + immd 地址处，
#   immd有12位，所以跳转范围 rs1 ± 2K
#
#   j immd                   // 相当于jal, x0, immd
#   用于无需返回的场景
#
#   jr rd                    // 相当于jalr, x0, 0(rd)
#   用于无需返回的场景

.text
.globl _start

_start:
    li x5, 1
    li x6, 1
    jal x7, sum
    li x7, 0xdeadbeef
    j stop

sum:
    add x5, x5, x6
    jalr x0, 0(x7)

stop:
    j stop

.end                                # end of file
