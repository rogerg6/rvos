
SRCS_ASM = \
	start.S \
	mem.S \
	entry.S \

SRCS_C = \
	kernel.c \
	uart.c \
	printf.c \
	page.c \
	sched.c \

DEFS +=

CROSS_COMPILE = riscv64-unknown-elf-
CFLAGS = -nostdlib -fno-builtin -march=rv32g -mabi=ilp32 -g -Wall

QEMU = qemu-system-riscv32
QFLAGS = -nographic -smp 1 -machine virt -bios none

GDB = gdb-multiarch
CC = ${CROSS_COMPILE}gcc
OBJDUMP = ${CROSS_COMPILE}objdump
OBJCOPY = ${CROSS_COMPILE}objcopy
MKDIR = mkdir -p
RM = rm -rf

OUTPUT_PATH = out

OBJS_ASM := $(addprefix ${OUTPUT_PATH}/, $(patsubst %.S, %.o, ${SRCS_ASM}))
OBJS_C   := $(addprefix ${OUTPUT_PATH}/, $(patsubst %.c, %.o, ${SRCS_C}))
OBJS = ${OBJS_ASM} ${OBJS_C}

ELF = ${OUTPUT_PATH}/os.elf
BIN = ${OUTPUT_PATH}/os.bin

USE_LINK_SCRIPT ?= true
ifeq (${USE_LINK_SCRIPT}, true)
LDFLAGS = -T ${OUTPUT_PATH}/os.ld.generated
else
LDFLAGS = -Ttext=0x80000000
endif

all: ${OUTPUT_PATH} ${ELF}

${OUTPUT_PATH}:
	@${MKDIR} $@

${ELF}: ${OBJS}
ifeq (${USE_LINK_SCRIPT}, true)
	${CC} -E -P -x c ${DEFS} ${CFLAGS} os.ld > ${OUTPUT_PATH}/os.ld.generated
endif
	${CC} ${CFLAGS} ${LDFLAGS} -o ${ELF} $^
	${OBJCOPY} -O binary ${ELF} ${BIN}

${OUTPUT_PATH}/%.o : %.c
	${CC} ${DEFS} ${CFLAGS} -c -o $@ $<

${OUTPUT_PATH}/%.o : %.S
	${CC} ${DEFS} ${CFLAGS} -c -o $@ $<


.PHONY: run debug code clean

run: all
	@echo "Press Ctrl-A and x to exit QEMU"
	@echo "-------------------------------"
	@echo "No output, please run 'make debug' to see details"
	@${QEMU} ${QFLAGS} -kernel ${ELF}

debug: all
	@echo "Press Ctrl-C and then input 'quit' to exit GDB and QEMU"
	@echo "-------------------------------"
	@${QEMU} ${QFLAGS} -kernel ${ELF} -s -S &
	@${GDB} ${ELF} -q -x ./gdbinit

code: all
	@${OBJDUMP} -S ${ELF} | less

clean:
	@${RM} ${OUTPUT_PATH}
