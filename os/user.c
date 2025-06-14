#include "os.h"

#define DELAY 1000
extern void trap_test(void);

void user_task0(void) {
    uart_puts("Task0 is created\n");
    while (1) {
        uart_puts("Task0: Running...\n");

#if TEST
        trap_test();
#endif
        task_delay(DELAY);
        task_yield();
    }
}

void user_task1(void) {
    uart_puts("Task1 is created\n");
    while (1) {
        uart_puts("Task1: Running...\n");
        task_delay(DELAY);
        task_yield();
    }
}

void create_tasks(void) {
    task_create(user_task0);
    task_create(user_task1);
}