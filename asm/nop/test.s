# nop 伪指令. 相当于 addi x0, x0, 0
#
# 空指令，什么都不做

.text
.globl _start

_start:
    nop

stop:
    j stop

.end                                # end of file
