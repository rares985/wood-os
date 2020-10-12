; A boot sector that enters 32-bit and loads the kernel
[org 0x7c00]
KERNEL_OFFSET equ 0x1000    ; Memory offset where the kernel will be loaded
    mov [BOOT_DRIVE], dl    ; BIOS stores the boot drive in DL,
                            ; might be useful later to store it here

    mov bp, 0x9000          ; Set up the stack
    mov sp, bp

    mov bx, MSG_REAL_MODE   ; Announce that we start in 16-bit real mode
    call print

    call load_kernel        ; Load our kernel

    call switch_pm

    jmp $


%include "print.asm"
%include "print_hex.asm"
%include "print_no_bios.asm"
%include "gdt.asm"
%include "switch_pm.asm"
%include "disk.asm"

[bits 16]
load_kernel:
    mov bx, MSG_LOAD_KERNEL         ; Print a message that we are loading the kernel
    call print

    mov bx, KERNEL_OFFSET           ; Set up parameters for disk_load routine, so that
    mov dh, 16                      ; the first 16 sectors are read from disk (excluding
    mov dl, [BOOT_DRIVE]            ; the boot sector) to address KERNEL_OFFSET
    call disk_load

    ret

; Here is where we arrive after switching to and initialising the 32bit protected mode
[bits 32]
BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print_no_bios
    call KERNEL_OFFSET      ; Give control to the kernel
    jmp $

; Global variables
BOOT_DRIVE db 0
MSG_LOAD_KERNEL db "Loading kernel into memory", 0
MSG_REAL_MODE db "Started in 16-bit Real Mode", 0
MSG_PROT_MODE db "Landed in 32-bit Protected Mode", 0

; Bootsector padding and magic number
times 510 - ($ - $$) db 0   ; Fill up to 510th byte with zeros
dw 0xAA55                   ; Last two bytes must be 55 and AA so BIOS knows we are a boot sector

