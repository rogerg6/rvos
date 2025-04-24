# la(Load Address)伪指令，相当于la = auipc + addi
#
# la rd, immd
# rd = immd, immd ∈ [0, 0xfffff]

.text
.globl _start

_start:
    la x5, _start
    jr x5

stop:
    j stop

.end                                # end of file
