# not ��αָ��൱�� xor rd, rs, -1
# not rd, rs
# rd = ~rs
#

.text
.globl _start

_start:
    li x6, 0xf0
    not x5, x6                  # x5 = ~x6

stop:
    j stop

.end                                # end of file
