
.text
.globl _start

_start:
    li x6, 1                        # x6 = 1
    li x7, 2                        # x7 = 2
    add x5, x6, x7                  # x5 = x6 + x7

    li x7, -2
    add x5, x6, x7

stop:
    j stop

.end                                # end of file