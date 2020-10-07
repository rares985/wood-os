
OS_IMAGE_FILE=os-image.bin

all: $(OS_IMAGE_FILE)

run:
	qemu-system-i386 -fda os-image.bin

$(OS_IMAGE_FILE): bootsect.bin
	cat $^ > $@

# Wildcard rule for compiling ASM to object
%.o: %.asm
	nasm -f elf $< -o $@

%.bin: %.asm
	nasm -f bin $< -o $@

clean:
	rm *.bin