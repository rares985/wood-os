; A boot sector that enters 32-bit protected mode.
[org 0x7c00]
    mov bp, 0x9000          ; Set the stack
    mov bp, sp

    mov bx, MSG_REAL_MODE
    call print

    call switch_pm

    jmp $

%include "print.asm"
%include "print_hex.asm"
%include "print_no_bios.asm"
%include "gdt.asm"
%include "switch_pm.asm"
%include "disk.asm"

; Here is where we arrive after switching to and initialising the 32bit protected mode
[bits 32]
BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print_no_bios
    jmp $

; Global variables
MSG_REAL_MODE db "Started in 16-bit Real Mode", 0
MSG_PROT_MODE db "Landed in 32-bit Protected Mode", 0

; Bootsector padding and magic number
times 510 - ($ - $$) db 0   ; Fill up to 510th byte with zeros
dw 0xAA55                   ; Last two bytes must be 55 and AA so BIOS knows we are a boot sector

