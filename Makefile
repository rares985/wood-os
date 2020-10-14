# Where to find input and store output
BUILD_DIR = build

# Output image file 
OS_IMAGE_FILE=$(BUILD_DIR)/os-image.bin

# Bootloader and kernel image paths
BOOTLOADER=$(BUILD_DIR)/bootloader/bootloader.bin
KERNEL=$(BUILD_DIR)/os/kernel/kernel.bin

export DEBUG

all: image
# Needed for recursive makes
# If this is not existent, Make will consider the targets already
# up to date if a folder with the same name exists.
.PHONY: bootloader os

image: bootloader os
	cat $(BOOTLOADER) $(KERNEL) > $(OS_IMAGE_FILE)

bootloader:
	$(info [Building bootloader...] )
	make -C bootloader

os:
	$(info [Building OS...])
	make -C os

run:
	qemu-system-i386 -fda $(OS_IMAGE_FILE)

debug:
	bochs -f bochsrc.txt

clean:
	make -C bootloader clean
	make -C os clean
	rm $(OS_IMAGE_FILE)