CC=/usr/local/i386elfgcc/bin/i386-elf-gcc
LD=/usr/local/i386elfgcc/bin/i386-elf-ld
CFLAGS=-Wall -Wextra -Werror -nostdlib -std=c99  -m32 -fno-builtin -fno-stack-protector -ffreestanding
CFLAGS+=-Idrivers -Ikernel -Icpu -Ilibc/include

BUILD_DIR = ../build/os

OS_SRCS = $(wildcard libc/**/*.c */*.c)
OS_ASMS = $(wildcard */*.asm)
OS_HDRS = $(wildcard */*.h)

OBJ = $(patsubst %.c, $(BUILD_DIR)/%.o, $(OS_SRCS))
OBJ += $(patsubst %.asm, $(BUILD_DIR)/%.o, $(OS_ASMS))

all: $(BUILD_DIR)/kernel/kernel.bin

$(BUILD_DIR)/kernel/kernel.bin: $(OBJ)
	$(LD) -T kernel.ld $^ -o $@

# Wildcard rule for compiling .c to .o
$(BUILD_DIR)/%.o: %.c ${OS_HDRS}
	$(CC) $(CFLAGS) -c $< -o $@

# Wildcard rule for compiling ASM to object
$(BUILD_DIR)/%.o: %.asm
	nasm -f elf $< -o $@

clean:
	rm $(OBJ)