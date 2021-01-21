LD=/usr/local/i386elfgcc/bin/i386-elf-ld

BUILD_ROOT = ../build
BUILD_DIR = $(BUILD_ROOT)/bootloader
IMAGE_NAME = bootloader.bin

all: dirs $(BUILD_DIR)/$(IMAGE_NAME)

$(BUILD_DIR)/$(IMAGE_NAME): $(BUILD_DIR)/boot0.bin $(BUILD_DIR)/boot1.bin
	cat $^ > $@

$(BUILD_DIR)/boot1.bin: $(BUILD_DIR)/boot1.o
	$(LD) $^ -T linker.ld -o $@

$(BUILD_DIR)/boot1.o: boot1.asm
	nasm -f elf $< -o $@

$(BUILD_DIR)/boot0.bin: boot0.asm
	nasm -f bin $< -o $@

dirs:
	mkdir -p $(BUILD_DIR)

clean:
	rm -f $(BUILD_DIR)/*
	rmdir $(BUILD_DIR)