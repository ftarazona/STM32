PREFIX	= arm-none-eabi-
CC		= $(PREFIX)gcc
AS		= $(PREFIX)as
LD		= $(PREFIX)gcc
DB		= gdb-multiarch

DEBUG	= DEBUG
DFLAGS	= -DSTM32L475xx -D__FPU_PRESENT -D$(DEBUG)
IFLAGS	= -Iinc -ICMSIS/Include -ICMSIS/Device/ST/STM32L4xx/Include
CFLAGS	= -std=gnu99 $(DFLAGS) $(IFLAGS) -g -O1 -Wall -Wextra -Werror -ffreestanding
FPUFLAGS	= -mfloat-abi=hard -mfpu=fpv4-sp-d16
TARGET_ARCH	= -mthumb -mcpu=cortex-m4 $(FPUFLAGS)

ASFLAGS	= -g
TARGET_MACH	= $(TARGET_ARCH)

ifeq ($(DEBUG), DEBUG)
	LDSCRIPT	= ld_ram.lds
else
	LDSCRIPT	= ld_flash.lds
endif
LDFLAGS	= -g -T $(LDSCRIPT) -nostdlib

OBJS	= crt0.o init.o memfuncs.o clocks.o main.o uart.o irq.o led.o button.o timer.o matrix.o
DEPS	= $(patsubst %.o, %.dep, $(OBJS))
EXE		= main.elf

.PHONY: clean all

vpath %.s libs
vpath %.h inc
vpath %.h CMSIS/Include
vpath %.h CMSIS/Device/ST/STM32L4xx/Include
vpath %.c src
vpath %.c libs

all: $(EXE)

$(EXE): $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@ $(LDLIBS)

# %.o : %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

%.dep : %.c
	$(CC) $(DFLAGS) $(IFLAGS) -MM $< -MF $@

-include $(DEPS)

clean:
	rm -f $(OBJS)

clean-all: clean
	rm -f $(EXE)
	rm -f $(DEPS)

connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir-LocalhostOnly

gdb:
	$(DB) $(EXE)
