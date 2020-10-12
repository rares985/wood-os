BUILD_DIR=../build/bootloader

OUT = $(BUILD_DIR)/bootloader.bin

all: $(OUT)

# Wildcard rule for compiling ASM to object
$(OUT): bootsect.asm
	nasm -f bin $< -o $@

clean:
	rm $(OUT)