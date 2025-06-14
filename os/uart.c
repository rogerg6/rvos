/*
 * Reference
 * [1]: TECHNICAL DATA ON 16550, http://byterunner.com/16550.html
 */

#include "platform.h"
#include "types.h"

#define UART_REG(reg) ((volatile uint8_t*)(UART0 + reg))

#define RHR 0	// Receive Holding Register (read mode)
#define THR 0	// Transmit Holding Register (write mode)
#define DLL 0	// LSB of Divisor Latch (write mode)
#define IER 1	// Interrupt Enable Register (write mode)
#define DLM 1	// MSB of Divisor Latch (write mode)
#define FCR 2	// FIFO Control Register (write mode)
#define ISR 2	// Interrupt Status Register (read mode)
#define LCR 3	// Line Control Register
#define MCR 4	// Modem Control Register
#define LSR 5	// Line Status Register
#define MSR 6	// Modem Status Register
#define SPR 7	// ScratchPad Register

#define LSR_RX_READY (1 << 0)
#define LSR_TX_IDLE  (1 << 5)

#define uart_read_reg(reg) (*(UART_REG(reg)))
#define uart_write_reg(reg, v) (*(UART_REG(reg)) = (v))

void uart_init(void){
    // disable interrupts
    uart_write_reg(IER, 0);

    /**
     * baudrate = 38.4k
     */
    uint8_t lcr = uart_read_reg(LCR);
    uart_write_reg(LCR, lcr | (1 << 7));
    uart_write_reg(DLL, 0x03);
    uart_write_reg(DLM, 0x00);

    // word length = 8bit
    lcr = 0;
    uart_write_reg(LCR, lcr | (3 << 0));

	/*
	 * enable receive interrupts.
	 */
	uint8_t ier = uart_read_reg(IER);
	uart_write_reg(IER, ier | (1 << 0));
}


int uart_putc(char ch)
{
	while ((uart_read_reg(LSR) & LSR_TX_IDLE) == 0);
	return uart_write_reg(THR, ch);
}

void uart_puts(char *s)
{
	while (*s) {
		uart_putc(*s++);
	}
}

int uart_getc(void)
{
	while (0 == (uart_read_reg(LSR) & LSR_RX_READY))
		;
	return uart_read_reg(RHR);
}

void uart_isr(void) {
    uart_putc((char)uart_getc());
    uart_putc('\n');
}