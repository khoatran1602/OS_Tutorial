#--------------------------------------Makefile-------------------------------------
CFILES = $(wildcard ./kernel/*.c)
OFILES = $(CFILES:./kernel/%.c=./build/%.o)

GCCFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib
LDFLAGS = -nostdlib 

all: clean kernel8.img run

./build/boot.o: ./kernel/boot.S
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

./build/uart.o: 
	aarch64-none-elf-gcc $(GCCFLAGS) -c ./uart/uart1.c -o $@

./build/%.o: ./kernel/%.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

kernel8.img: ./build/boot.o ./build/uart.o $(OFILES)
	aarch64-none-elf-ld $(LDFLAGS) ./build/boot.o ./build/uart.o $(OFILES)  -T ./kernel/link.ld -o ./build/kernel8.elf
	aarch64-none-elf-objcopy -O binary ./build/kernel8.elf kernel8.img

clean:
	del *.img .\build\*.elf .\build\*.o

run:
ifdef UART0
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial stdio
else #UART1
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial null -serial stdio
endif



