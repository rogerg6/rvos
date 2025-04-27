# store 存储数据到内存
#
# format:
#   store rs, immd(rd)    //*(rd+immd) = rs
#
# note: immd ∈ [-2048, 2047)
# 
# sb, sh, sw

.text
.globl _start

_start:
    la x5, array
    li x6, 0x12345678
    sb x6, 0(x5)            # array[0] = 0x78
    sh x6, 0(x5)            # array[0] = 0x5678
    sw x6, 0(x5)            # array[0] = 0x12345678

    # 读出来验证一下
    lw x7, 0(x5)

stop:
    j stop

array:
    .byte 0x00
    .byte 0x00
    .byte 0x00
    .byte 0x00

.end                                # end of file
