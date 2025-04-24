# mv 伪指令. 相当于 addi rd, rs, 0
#
# mv rd, rs
# rd = rs
# 把rs中的值赋值给rd

.text
.globl _start

_start:
    li x6, 30
    mv x5, x6

stop:
    j stop

.end                                # end of file
