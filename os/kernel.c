
#include "os.h"


#if TEST
extern void page_test(void);
#endif

void start_kernel(void) {
    uart_init();
    uart_puts("Hello RVOS ! ");
    printf("Author: %c%s%d\n", 'r', "ogerg", 6);

    page_init();
#if TEST
    page_test();
#endif

    trap_init();

    plic_init();

    timer_init();

    sched_init();
    create_tasks();
    schedule();

    uart_puts("Never go here !\n");
    while (1) { }
}