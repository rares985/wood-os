[org 0x7c00]
[bits 16]

BOOT1_OFFSET equ 0x1000     ; This is the location where boot1
                            ; will be loaded into RAM.


boot0:
    cli                     ; 1. Disable interrupts
    jmp 0:boot0_far         ; 2. Canonicalize CS:EIP

boot0_far:
    mov bp, 0x7000          ; 3. Set up the stack
    mov sp, bp

    sti                     ; 4. Enable interrupts

                            ; 5. Load boot1 into memory, starting at address 0x1000
    mov bx, BOOT1_OFFSET    ;    BX - pointer to storage location
    mov dh, 16              ;    DH - how many sectors to read (16 sectors = 8K)
    mov cl, 2               ;    CL - sector at which to start: 2 (right after the boot sector)
                            ;    DL - stores the boot drive (thank you BIOS)
    call disk_load
    call BOOT1_OFFSET       ; 6.  Pass control to boot1
    jmp $                   ;     If control is ever returned to boot0, hang


%include "disk.asm"
%include "print.asm"
%include "print_hex.asm"

times 510 - ($ - $$) db 0   ; Pad with zeros until 509th byte inclusively,
dw 0xAA55                   ; and last two bytes must be 55 and AA so BIOS knows we are a boot sector