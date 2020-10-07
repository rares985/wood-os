; Simple boot sector implementation

[org 0x7c00]                ; Tell the assembler code will be loaded at this address
    mov bp, 0x8000
    mov bp, sp

    mov bx, 0x9000
    mov dh, 2
    call disk_load
    mov dx, [0x9000]
    call print_hex
    mov dx, [0x9000+512]
    call print_hex

jmp $

%include "print.asm"
%include "print_hex.asm"
%include "disk.asm"

times 510 - ($ - $$) db 0   ; Fill up to 510th byte with zeros
dw 0xAA55                   ; Last two bytes must be 55 and AA so BIOS knows we are a boot sector

times 256 dw 0xdada
times 256 dw 0xface