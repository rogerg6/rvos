# li(Load immdiate) 伪指令. 相当于li = lui + addi
#
# lui rd, immd
# rd = immd 
# immd ∈ [0, 0xffffffff]
# 把一个立即数保存到寄存器
#

.text
.globl _start

_start:
    li x5, 0x80
    li x6, 0x12345678
    li x7, 0x12345fff

stop:
    j stop

.end                                # end of file
