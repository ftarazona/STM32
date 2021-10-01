CC = arm-none-eabi-gcc
DP = arm-none-eabi-objdump

all: base_dump static_dump const2_dump pointer_dump

base_dump: base
	$(DP) -h $<_0.o > $@_0
	$(DP) -d $<_0.o >> $@_0
	$(DP) -h $<_1.o > $@_1
	$(DP) -d $<_1.o >> $@_1
	$(DP) -h $<_2.o > $@_2
	$(DP) -d $<_2.o >> $@_2
	$(DP) -h $<_s.o > $@_s
	$(DP) -d $<_s.o >> $@_s

static_dump: static
	$(DP) -h $<_0.o > $@_0
	$(DP) -d $<_0.o >> $@_0
	$(DP) -h $<_1.o > $@_1
	$(DP) -d $<_1.o >> $@_1
	$(DP) -h $<_2.o > $@_2
	$(DP) -d $<_2.o >> $@_2
	$(DP) -h $<_s.o > $@_s
	$(DP) -d $<_s.o >> $@_s

pointer_dump: pointer
	$(DP) -h $<_0.o > $@_0
	$(DP) -d $<_0.o >> $@_0
	$(DP) -h $<_1.o > $@_1
	$(DP) -d $<_1.o >> $@_1
	$(DP) -h $<_2.o > $@_2
	$(DP) -d $<_2.o >> $@_2
	$(DP) -h $<_s.o > $@_s
	$(DP) -d $<_s.o >> $@_s

const2_dump: const2
	$(DP) -h $<_0.o > $@_0
	$(DP) -d $<_0.o >> $@_0
	$(DP) -h $<_1.o > $@_1
	$(DP) -d $<_1.o >> $@_1
	$(DP) -h $<_2.o > $@_2
	$(DP) -d $<_2.o >> $@_2
	$(DP) -h $<_s.o > $@_s
	$(DP) -d $<_s.o >> $@_s

base: ex3.c
	$(CC) -c $< -o $@_0.o -O0
	$(CC) -c $< -o $@_1.o -O1
	$(CC) -c $< -o $@_2.o -O2
	$(CC) -c $< -o $@_s.o -Os

static: ex3_static.c
	$(CC) -c $< -o $@_0.o -O0
	$(CC) -c $< -o $@_1.o -O1
	$(CC) -c $< -o $@_2.o -O2
	$(CC) -c $< -o $@_s.o -Os

const2: ex3_const2.c
	$(CC) -c $< -o $@_0.o -O0
	$(CC) -c $< -o $@_1.o -O1
	$(CC) -c $< -o $@_2.o -O2
	$(CC) -c $< -o $@_s.o -Os

pointer: ex3_pointer.c
	$(CC) -c $< -o $@_0.o -O0
	$(CC) -c $< -o $@_1.o -O1
	$(CC) -c $< -o $@_2.o -O2
	$(CC) -c $< -o $@_s.o -Os
