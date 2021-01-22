CC=/usr/local/i386elfgcc/bin/i386-elf-gcc
LD=/usr/local/i386elfgcc/bin/i386-elf-ld
CFLAGS=-nostdlib -std=c99 -m32 -fno-builtin -fno-stack-protector -ffreestanding
CFLAGS+=-Wall -Wextra -Werror
CFLAGS+=-Idrivers -Ikernel -Icpu -Ilibc/include -Ikernel/include -std=c99

ifdef DEBUG
CFLAGS+=-g
endif

BUILD_DIR = ../build/os

OS_SRCS = $(wildcard libc/**/*.c */*.c)
OS_HDRS = $(wildcard */*.h)

OBJ = $(patsubst %.c, $(BUILD_DIR)/%.o, $(OS_SRCS))

OBJS = $(BUILD_DIR)/kernel/kernel_call.o $(BUILD_DIR)/cpu/interrupt.o $(BUILD_DIR)/kernel/paging.o $(OBJ) 

ifdef DEBUG
all: image elf
else
all: image
endif

# Debug rules --------------------
elf: $(BUILD_DIR)/kernel/kernel.elf

$(BUILD_DIR)/kernel/kernel.elf: $(OBJS)
	$(LD) -T kernel.ld $^ -o $@

image: dirs $(BUILD_DIR)/kernel/kernel.bin

$(BUILD_DIR)/kernel/kernel.bin: $(OBJS)
	$(LD) -T kernel.ld $^ -o $@

# Wildcard rule for compiling .c to .o
$(BUILD_DIR)/%.o: %.c ${OS_HDRS}
	$(CC) $(CFLAGS) -c $< -o $@

# Wildcard rule for compiling ASM to object
$(BUILD_DIR)/%.o: %.asm
	nasm -f elf $< -o $@

dirs:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/kernel
	mkdir -p $(BUILD_DIR)/cpu
	mkdir -p $(BUILD_DIR)/drivers
	mkdir -p $(BUILD_DIR)/libc
	mkdir -p $(BUILD_DIR)/libc/stdlib
	mkdir -p $(BUILD_DIR)/libc/stdio
	mkdir -p $(BUILD_DIR)/libc/string

clean:
	rm -f $(BUILD_DIR)/libc/stdlib/*
	rmdir $(BUILD_DIR)/libc/stdlib
	rm -f $(BUILD_DIR)/libc/stdio/*
	rmdir $(BUILD_DIR)/libc/stdio
	rm -f $(BUILD_DIR)/libc/string/*
	rmdir $(BUILD_DIR)/libc/string
	rm -f $(BUILD_DIR)/libc/*
	rmdir $(BUILD_DIR)/libc
	rm -f $(BUILD_DIR)/drivers/*
	rmdir $(BUILD_DIR)/drivers/
	rm -f $(BUILD_DIR)/kernel/*
	rmdir $(BUILD_DIR)/kernel
	rm -f $(BUILD_DIR)/cpu/*
	rmdir $(BUILD_DIR)/cpu
	rm -f $(BUILD_DIR)/*
	rmdir $(BUILD_DIR)