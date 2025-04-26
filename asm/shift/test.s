# Shift Instruction
# Âß¼­ÒÆÎ»£º
#   zero extend
#   sll, slli, srl, srli
#   immd ¡Ê [-2048, 204)
# ËãÊýÒÆÎ»£º
#   signed extend
#   sra, srai

.text
.globl _start

_start:
    li x6, 3
    li x7, 2
    sll x5, x6, x7                  # x5 = x6 << x7
    srl x5, x5, x7                  # x5 = x5 >> x7

    li x6, 0x300
    slli x5, x6, 4                  # x5 = x6 << 4
    srli x5, x5, 4                  # x5 = x5 >> 4

    li x6, 0x80000000
    li x7, 4
    sra x5, x6, x7                  # x5 = x6 >> x7
    srai x5, x5, 4                  # x5 = x5 >> 4

stop:
    j stop

.end                                # end of file
