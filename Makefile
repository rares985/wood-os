CC=/usr/local/i386elfgcc/bin/i386-elf-gcc
CFLAGS=-Wall -Wextra -Werror

LD=/usr/local/i386elfgcc/bin/i386-elf-ld

C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)
# Nice syntax for file extension replacement

OBJ = ${C_SOURCES:.c=.o}

OS_IMAGE_FILE=os-image.bin

$(OS_IMAGE_FILE): boot/bootsect.bin kernel.bin
	cat $^ > $@


kernel.bin: boot/kernel.o $(OBJ)
	$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary

# Wildcard rule for compiling .c to .o
%.o: %.c ${HEADERS}
	$(CC) $(CFLAGS) -ffreestanding -c $^ -o $@

# Wildcard rule for compiling ASM to object
%.o: %.asm
	nasm -f elf $< -o $@

%.bin: %.asm
	nasm -f bin $< -o $@

run:
	qemu-system-i386 -fda os-image.bin

clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o