SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=%.o)
CFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib

all: clean kernel8.img #run

boot.o: boot.S
	aarch64-none-elf-gcc $(CFLAGS) -c boot.S -o boot.o

%.o: %.c
	aarch64-none-elf-gcc $(CFLAGS) -c $< -o $@

kernel8.img: boot.o $(OBJS)
	aarch64-none-elf-ld -nostdlib boot.o $(OBJS) -T link.ld -o kernel8.elf
	aarch64-none-elf-objcopy -O binary kernel8.elf kernel8.img

clean:
	del kernel8.elf *.o *.img

run:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial null -serial stdio

test: all run