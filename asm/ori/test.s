# ori rd, rs1, immd
# rd = rs1 | immd
#
# immd �� [-2048, 2047)

.text
.globl _start

_start:
    li x6, 0xf0
    ori x5, x6, 0xcc                  # x5 = x6 | 0xcc

stop:
    j stop

.end                                # end of file
