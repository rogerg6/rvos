#include "os.h"

#define DELAY 1000
extern void trap_test(void);

void user_task0(void) {
    uart_puts("Task0 is created\n");
    task_yield();
    while (1) {
#ifdef USE_LOCK
        spin_lock();

        uart_puts("Task 0: Begin ... \n");
        for (int i = 0; i < 5; ++i) {
            uart_puts("Task0: Running...\n");
            task_delay(DELAY);
        }
        uart_puts("Task 0: End ... \n");

        spin_unlock();
#else
        uart_puts("Task0: Running...\n");
#if TEST
        trap_test();
#endif
        task_delay(DELAY);
#endif
    }
}

void user_task1(void) {
    uart_puts("Task1 is created\n");
    while (1) {
        uart_puts("Task1: Running...\n");
        task_delay(DELAY);
    }
}

void create_tasks(void) {
    task_create(user_task0);
    task_create(user_task1);
}