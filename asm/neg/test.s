# neg(Negtive) 伪指令，相当于sub rd, x0, rs
# 
# neg rd, rs
# rd = -rs

.text
.globl _start

_start:
    li x5, 1
    neg x6, x5

stop:
    j stop

.end                                # end of file
