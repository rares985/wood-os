CC=/usr/local/i386elfgcc/bin/i386-elf-gcc
CFLAGS=-Wall -Wextra -Werror -nostdlib -std=c99  -m32 -fno-builtin -fno-stack-protector
CFLAGS+=-Iinclude

BUILD_DIR = ../build/libc

LIBC_SRCS := $(wildcard */*.c)
LIBC_HDRS := $(wildcard include/*.h)
LIBC_OBJS := $(patsubst %.c, $(BUILD_DIR)/%.o, $(LIBC_SRCS))


all: $(LIBC_OBJS)

# Wildcard rule for compiling .c to .o
$(BUILD_DIR)/%.o: %.c ${LIBC_HDRS}
	$(CC) $(CFLAGS) -ffreestanding -c $< -o $@

clean:
	rm $(BUILD_DIR)/*.o