#variables

CC = $(TOOLPATH_COMPILER)/bin/arm-eabi-gcc.exe
MACH = cortex-m4
STD = gnu11
CFLAGS = -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=$(STD) -O0

# Now add command and flags for linker 
# -T is used for linker
# -nostdlib is used for not include statndard libary (printf,scanf won't work)
# -mfloat-abi=soft : used for floating point calculation

LDFLAGS = -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nosys.specs -T stm32_ls.ld -Wl,-Map=final.map

all: main.o led.o startup.o syscalls.o final.elf

# output file : source files needed for op file
#	then write the instruction or recipe

# $@ -> output file. Ex - main.o
# $^ -> source files. Ex - main.c .. 

main.o : main.c
	$(CC) $(CFLAGS) -o $@ $^

led.o : led.c
	$(CC) $(CFLAGS) -o $@ $^

startup.o : stm32_startup.c
	$(CC) $(CFLAGS) -o $@ $^

syscalls.o : syscalls.c
	$(CC) $(CFLAGS) -o $@ $^

final.elf : main.o led.o startup.o syscalls.o
	$(CC) $(LDFLAGS) -o $@ $^


clean:
	rm -rf *.o *.elf

.PHONY: clean all