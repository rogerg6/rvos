# xor rd, rs1, rs2
# rd = rs1 ^ rs2
#

.text
.globl _start

_start:
    li x6, 0xf0
    li x7, 0x0f
    xor x5, x6, x7                  # x5 = x6 ^ x7

stop:
    j stop

.end                                # end of file
