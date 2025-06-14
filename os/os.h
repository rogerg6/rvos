
#ifndef __OS_H__
#define __OS_H__

#include "types.h"
#include "platform.h"
#include "riscv.h"

#include <stddef.h>
#include <stdarg.h>

/* task management */
struct context {
	/* ignore x0 */
	reg_t ra;
	reg_t sp;
	reg_t gp;
	reg_t tp;
	reg_t t0;
	reg_t t1;
	reg_t t2;
	reg_t s0;
	reg_t s1;
	reg_t a0;
	reg_t a1;
	reg_t a2;
	reg_t a3;
	reg_t a4;
	reg_t a5;
	reg_t a6;
	reg_t a7;
	reg_t s2;
	reg_t s3;
	reg_t s4;
	reg_t s5;
	reg_t s6;
	reg_t s7;
	reg_t s8;
	reg_t s9;
	reg_t s10;
	reg_t s11;
	reg_t t3;
	reg_t t4;
	reg_t t5;
	reg_t t6;
};

#define TEST 0

/* uart */
extern void uart_init(void);
extern int uart_putc(char ch);
extern void uart_puts(char *s);
extern void uart_isr(void);

/* printf */
extern int  printf(const char* s, ...);
extern void panic(char *s);

/* memory management */
extern void page_init(void);
extern void *page_alloc(int npages);
extern void page_free(void *p);

/* task management */
extern void sched_init(void);
extern void schedule(void);
extern int task_create(void(*task)(void));
extern void task_yield(void);
extern void task_delay(volatile int count);
extern void create_tasks(void);

/* trap management */
extern void trap_init(void);

/* interrpupt management */
void plic_init(void);
int plic_claim(void);
void plic_complete(int irq);


#endif /* __OS_H__ */
