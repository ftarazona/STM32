PREFIX	= arm-none-eabi-
CC		= $(PREFIX)gcc
AS		= $(PREFIX)as
LD		= $(PREFIX)gcc
DB		= gdb-multiarch

DEBUG	= -DDEBUG
DFLAGS	= -DSTM32L475xx -D__FPU_PRESENT $(DEBUG)
IFLAGS	= -Iinc -ICMSIS/Include -ICMSIS/Device/ST/STM32L4xx/Include
FPUFLAGS	= -mfloat-abi=hard -mfpu=fpv4-sp-d16
TARGET_ARCH	= -mthumb -mcpu=cortex-m4 $(FPUFLAGS)
CFLAGS	= -std=gnu99 $(FPUFLAGS) $(TARGET_ARCH) $(DFLAGS) $(IFLAGS) -g -O1 -Wall -Wextra -Werror -ffreestanding

ASFLAGS	= $(FPUFLAGS) $(TARGET_ARCH) -g
TARGET_MACH	= $(TARGET_ARCH)

ifeq ($(DEBUG), -DDEBUG)
	LDSCRIPT	= ld_ram.lds
else
	LDSCRIPT	= ld_flash.lds
endif
LDFLAGS	= -g -T $(LDSCRIPT) -nostdlib

DRIVERS	= $(patsubst drivers/%.c, build/%.o, $(wildcard drivers/*.c))
LIBS	= $(patsubst libs/%.c, build/%.o, $(wildcard libs/*.c))
ASM		= $(patsubst libs/%.s, build/%.o, $(wildcard libs/*.s))
OBJS	= $(ASM) $(LIBS) $(DRIVERS) build/snake.o
DEPS	= $(patsubst build/%.o, dep/%.dep, $(OBJS))
EXE		= main.elf

.PHONY: clean all

vpath %.s libs
vpath %.c src
vpath %.c drivers
vpath %.c libs

all: $(EXE)

$(EXE): $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@ $(LDLIBS)

build/%.o : %.c
	echo $(OBJS)
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o : %.s
	$(AS) $(ASFLAGS) $< -o $@

%.dep : %.c
	$(CC) $(DFLAGS) $(IFLAGS) -MM $< -MF $@

-include $(DEPS)

clean:
	rm -f $(EXE)
	rm -f build/*

clean-all: clean
	rm -f 
	rm -f dep/*

connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir-LocalhostOnly

gdb:
	$(DB) $(EXE)

send_frames:
	rsc/stty.sh
	cat rsc/many_frames.bin > /dev/ttyACM0
