KERNEL_OFFSET     equ 0xF000


[bits 16]
boot1:
    pusha
    mov bp, 0x7000                      ; 1. Set up the stack pointer.
    mov sp, bp

    ; Broken, for now.
    ; call do_e820                      ; 2. Query BIOS for available memory. This can only be done in
                                        ;    real mode, so perform it before switching to protected
                                        ;    mode

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



; Function which loads the kernel into memory, starting at KERNEL_OFFSET.
; According to our memory map, we have around 576K of free memory (F000 - 0x9F000)
; For now, read only 32 sectors (16K) from the disk.
load_kernel:
    pusha
                                        ;  DL - drive from which to read (placed here by BIOS)
    mov dh, 64                          ;  DH - how many sectors to read
    mov ax, 17                          ;  AX - LBA address of sector from which to start (1 from boot0 + 16 from boot1 = 17 occupied)

    mov bx, KERNEL_OFFSET               ; We want to load the kernel at KERNEL_OFFSET.
    call disk_load

    popa
    ret



%include "disk.asm"
%include "print.asm"
%include "print_hex.asm"
%include "gdt.asm"
%include "e820.asm"

; 32-bit includes
%include "print_no_bios.asm"

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


    mov ebp, 0x90000                    ;   Set up stack for protected mode
    mov esp, ebp

    mov ebx, HELLO_PROT
    call print_no_bios
    xchg bx, bx
    call KERNEL_OFFSET                  ; 8. Give control to the kernel
    jmp $                               ;    If control is ever returned, hang here

HELLO_PROT db "protected mode!", 0


; Recall that in boot0 we read 16 sectors from boot drive.
; 16 * 512 bytes = 8K of data. Therefore, we must read from
; boot disk, starting with sector 18 if we want to read the kernel.
; In order to do this, we must make the boot1 occupy exactly 8K due
; to how the OS is built, otherwise in the OS image the 8K will span 
; both boot1 and some parts of the kernel. So we are padding from current
; address up until 8192 with zeros.
times 8192 - ($ - $$) db 0
