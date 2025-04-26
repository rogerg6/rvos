# Load 从内存读取数据
#
# format:
#   lb rd, immd(rs)    //rd = *(rs+immd)
#
# note: immd ∈ [-2048, 2047)
# 
# lb, lh     符号扩展
# lbu, lhu   0扩展
# lw

.text
.globl _start

_start:
    la x5, array
    lb x6, 0(x5)            # x6 = 0x11
    lb x7, 1(x5)            # x7 = 0xffffffff

    lbu x6, 0(x5)            # x6 = 0x11
    lbu x7, 1(x5)            # x7 = 0xff

    lh x6, 0(x5)            # x6 = 0xffffff11
    lhu x6, 0(x5)            # x6 = 0xff11

    lw x6, 0(x5)            # x6 = 0xbbaaff11
stop:
    j stop

array:
    .byte 0x11
    .byte 0xff
    .byte 0xaa
    .byte 0xbb

.end                                # end of file
