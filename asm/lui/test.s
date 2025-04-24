# lui(Load upper immdiate)
# lui rd, immd
# rd = immd << 12
# immd ∈ [0, 0xfffff]
# 把一个立即数左移12位保存到寄存器，低12位清0

.text
.globl _start

_start:
    li x6, 1
    lui x6, 0x12345               # x6 = 0x12345 << 12 = 0x12345000

stop:
    j stop

.end                                # end of file
