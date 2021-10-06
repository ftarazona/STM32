PREFIX	= arm-none-eabi-
CC		= $(PREFIX)gcc
AS		= $(PREFIX)as
LD		= $(PREFIX)gcc
DB		= gdb-multiarch

DFLAGS	= -DSTM32L475xx -D__FPU_PRESENT
IFLAGS	= -Iinc -ICMSIS/Include -ICMSIS/Device/ST/STM32L4xx/Include
CFLAGS	= -std=gnu99 $(DFLAGS) $(IFLAGS) -g -O2 -Wall -Wextra -Werror
FPUFLAGS	= -mfloat-abi=hard -mfpu=fpv4-sp-d16
TARGET_ARCH	= -mthumb -mcpu=cortex-m4 $(FPUFLAGS)

ASFLAGS	= -g
TARGET_MACH	= $(TARGET_ARCH)

LDSCRIPT	= ld_ram.lds
LDFLAGS	= -g -T $(LDSCRIPT) -nostdlib

OBJS	= crt0.o init.o clocks.o main.o uart.o irq.o
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
	mv clocks.o clocks.o.bak
	rm -f $(OBJS)
	mv clocks.o.bak clocks.o

clean-all: clean
	rm -f $(EXE)
	rm -f $(DEPS)

connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir-LocalhostOnly

gdb:
	$(DB) $(EXE)	
