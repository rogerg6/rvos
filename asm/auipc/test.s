# auipc(Add Upper Immdiate Program Counter)
#
# auipc rd, immd
# rd = immd<<12 + pc, immd ∈ [0, 0xfffff]

.text
.globl _start

_start:
    auipc x5, 0x12345       # x5 = pc + 0x12345
    auipc x6, 0             # x6 = pc + 0x0

stop:
    j stop

.end                                # end of file
