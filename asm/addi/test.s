# addi 含立即数的加法
# 立即数只有12bit[-2048, 2047)，运算的时候执行符号扩展为32bit

.text
.globl _start

_start:
    li x6, 1                         # x6 = 1
    addi x5, x6, 0x123               # x5 = x6 + 0x123

stop:
    j stop

.end                                # end of file
