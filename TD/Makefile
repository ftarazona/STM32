PREFIX	= arm-none-eabi-
CC		= $(PREFIX)gcc
AS		= $(PREFIX)as
LD		= $(PREFIX)gcc
DB		= gdb-multiarch

CFLAGS	= -I inc -g -O2
FPUFLAGS	= -mfloat-abi=hard -mfpu=fpv4-sp-d16
TARGET_ARCH	= -mthumb -mcpu=cortex-m4 $(FPUFLAGS)

ASFLAGS	= -g
TARGET_MACH	= $(TARGET_ARCH)

LDSCRIPT	= ld_ram.lds
LDFLAGS	= -g -T $(LDSCRIPT) -nostdlib

OBJS	= crt0.o main.o fibo.o
DEPS	= $(patsubst %.o, %.dep, $(OBJS))
EXE		= main.elf

.PHONY: clean all

vpath %.s libs
vpath %.h inc
vpath %.c src
vpath %.c libs

all: $(EXE)

$(EXE): $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@ $(LDLIBS)

# %.o : %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

%.dep : %.c
	$(CC) -I inc -MM $< -MF $@

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
