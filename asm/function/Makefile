CROSS_COMPILE = riscv64-unknown-elf-
CFLAGS = -nostdlib -fno-builtin -march=rv32g -mabi=ilp32 -g -Wall

QEMU = qemu-system-riscv32
QFLAGS = -nographic -smp 1 -machine virt -bios none

GDB = gdb-multiarch
CC = ${CROSS_COMPILE}gcc
OBJDUMP = ${CROSS_COMPILE}objdump
OBJCOPY = ${CROSS_COMPILE}objcopy

EXEC = cc_leaf cc_nested
SRC = $(EXEC:=.s)
GDBINIT = ./gdbinit

all:
	for src in $(SRC); do \
		obj=$${src%.s};  \
		${CC} ${CFLAGS} $$src -Ttext=0x80000000 -o $${obj}.elf; \
		${OBJCOPY} -O binary $${obj}.elf $${obj}.bin; \
	done

run_leaf: all
	@echo "Press Ctrl-C and then input 'quit' to exit GDB and QEMU"
	@echo "-------------------------------"
	@${QEMU} ${QFLAGS} -kernel cc_leaf.elf -s -S &
	@${GDB} cc_leaf.elf -q -x ${GDBINIT}

run_nested: all
	@echo "Press Ctrl-C and then input 'quit' to exit GDB and QEMU"
	@echo "-------------------------------"
	@${QEMU} ${QFLAGS} -kernel cc_nested.elf -s -S &
	@${GDB} cc_nested.elf -q -x ${GDBINIT}


code_leaf: all
	@${OBJDUMP} -S cc_leaf.elf | less

code_nested: all
	@${OBJDUMP} -S cc_nested.elf | less

clean:
	rm -rf *.o *.bin *.elf
