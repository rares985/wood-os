file build/os-image.bin
symbol-file build/os/kernel/kernel.elf
set architecure i8086
target remote localhost:26000
layout asm
layout reg
b *0x7c00