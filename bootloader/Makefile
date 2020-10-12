CC=/usr/local/i386elfgcc/bin/i386-elf-gcc
LD=/usr/local/i386elfgcc/bin/i386-elf-ld
CFLAGS=-Wall -Wextra -Werror -nostdlib -std=c99  -m32 -fno-builtin -fno-stack-protector
CFLAGS+=-Idrivers -Ikernel -Icpu -Ilibc/include

BUILD_DIR=../build/bootloader

OUT = $(BUILD_DIR)/bootloader.bin

all: $(OUT)

# Wildcard rule for compiling ASM to object
$(OUT): bootsect.asm
	nasm -f bin $< -o $@

clean:
	rm $(OUT)