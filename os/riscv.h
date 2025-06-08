
#ifndef __RISCV_H
#define __RISCV_H

#include "types.h"

static inline void w_mscratch(reg_t x) {
    asm volatile ("csrw mscratch, %0" : : "r"(x));
}

static inline void w_mtvec(reg_t x) {
    asm volatile ("csrw mtvec, %0" : : "r"(x));
}

/* Machine-mode Cause Masks */
#define MCAUSE_MASK_INTERRUPT	(reg_t)0x80000000
#define MCAUSE_MASK_ECODE	(reg_t)0x7FFFFFFF

#endif