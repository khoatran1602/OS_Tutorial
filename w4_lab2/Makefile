CFILES = $(wildcard ./src/*.c)
OFILES = $(CFILES:./src/%.c=./build/%.o)

GCCFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib
LDFLAGS = -nostdlib

all: clean kernel8.img run

ifdef UART3
UARTTYPE = 3
else #UART4
UARTTYPE = 4
endif

GCCFLAGS += -DUART$(UARTTYPE)

./build/boot.o: ./src/boot.S
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

# Handle UART file selection based on UARTTYPE
ifeq ($(UARTTYPE), 3)
UARTFILE = ./src/uart/uart3.c
else
UARTFILE = ./src/uart/uart4.c
endif

./build/uart.o: $(UARTFILE)
	aarch64-none-elf-gcc $(GCCFLAGS) -c $(UARTFILE) -o $@

./build/%.o: ./src/%.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

kernel8.img: ./build/boot.o ./build/uart.o $(OFILES)
	aarch64-none-elf-ld $(LDFLAGS) ./build/boot.o ./build/uart.o $(OFILES) -T ./src/link.ld -o ./build/kernel8.elf
	aarch64-none-elf-objcopy -O binary ./build/kernel8.elf kernel8.img

clean:
	del *.img .\build\*.elf .\build\*.o

run:
ifdef UART3
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial stdio
else #UART4
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial null -serial stdio
endif
