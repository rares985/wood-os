KERNEL_OFFSET equ 0xF000

[bits 16]
boot1:
    pop dx                              ; Save the boot drive - stack will be overwritten
    mov bp, 0x7000                      ; 1. Set up the stack pointer.
    mov sp, bp
    push dx                             ; Store it on the new stack

    xchg bx, bx

    ; Broken, for now.
    ; call do_e820                        ; 2. Query BIOS for available memory. This can only be done in
                                        ;    real mode, so perform it before switching to protected
                                        ;    mode

    xchg bx, bx
    call load_kernel                    ; 3. Load the kernel from disk and map it into memory,
                                        ;    using the exact same methods we used for the transition
                                        ;    boot0 -> boot1.

    cli                                 ; 4. Disable interrupts until the protected mode 
                                        ;    interrupt vector is set up or interrupts go wild

    lgdt [gdt_descriptor]               ; 5. Load the GDT, which defines the protected mode
                                        ;    segments (code and data)

    mov eax, cr0                        ; 6. Switch to protected mode. For this, the first bit
    or eax, 0x1                         ;    of CR0, a control register, must be set.
    mov cr0, eax

    jmp CODE_SEG:initialise_pm          ; 7. Make a far jump (actually not so far, just tricking
                                        ;    the CPU ) to our 32-bit code. This forces the CPU
                                        ;    to flush its cache of pre-fetched instructions.

    mov ebx, HELLO_PROT
    call print_no_bios

    call KERNEL_OFFSET                  ; 8. Give control to the kernel
    jmp $                               ;    If control is ever returned, hang here


; Function which loads the kernel into memory, starting at KERNEL_OFFSET.
; According to our memory map, we have around 576K of free memory (0xF000 - 0x9F0000)
; For now, read only 64 sectors (32K) from the disk.
load_kernel:
    mov bx, KERNEL_OFFSET               ;  BX - pointer to storage
    pop dx                              ;  DL - drive from which to read (stored in boot0 on stack)
    mov dh, 64                          ;  DH - how many sectors to read
    call disk_load
    ret


; Function which initialises the protected mode:
;  - segment registers must point to the new data selector defined in GDT
;  - stack must be set up again, since protected mode can address a lot more memory
[bits 32]
initialise_pm:
    mov ax, DATA_SEG                    ;  Since we are in PM, old segments have no longer a meaning
    mov ds, ax                          ;  we must point our segment registers to the data selector defined in GDT
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    xchg bx, bx

    mov ebp, 0x90000                    ;   Set up stack for protected mode
    mov esp, ebp
    ret


%include "disk.asm"
%include "print.asm"
%include "print_hex.asm"
%include "gdt.asm"
%include "print_no_bios.asm"
%include "e820.asm"

HELLO_PROT db "protected mode!", 0
