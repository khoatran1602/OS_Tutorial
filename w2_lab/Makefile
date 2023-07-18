CFILES = $(wildcard *.c)        # Get a list of all .c files in the current directory
OFILES = $(CFILES:.c=.o)        # Generate a list of corresponding .o files
# -Wall: enable all warnings
# -O2: optimization level 2
# -ffreestanding: indicate that the program does not use the standard library
# -nostdinc: do not search the standard system directories for header files
# -nostdlib: do not link with standard system libraries
GCCFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib

all: clean kernel8.img         # Default target: clean and build kernel8.img

boot.o: boot.S                # Compile boot.S into object file boot.o
	aarch64-none-elf-gcc $(GCCFLAGS) -c boot.S -o boot.o

%.o: %.c                      # Compile .c files into object files using GCC
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

kernel8.img: boot.o $(OFILES)  # Link boot.o and other object files into kernel8.elf
	aarch64-none-elf-ld -nostdlib boot.o $(OFILES) -T link.ld -o kernel8.elf
	aarch64-none-elf-objcopy -O binary kernel8.elf kernel8.img

clean:                        # Clean up generated files
	del kernel8.elf *.o *.img
