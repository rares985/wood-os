; Function which switches to 32-bit protected mode.
;
;
;
;
[bits 16]
switch_pm:
    cli                                 ; Disable interrupts until the protected mode 
                                        ; interrupt vector is set up or interrupts go wild

    lgdt [gdt_descriptor]               ; Load the GDT, which defines the protected mode
                                        ; segments (code and data)

    mov eax, cr0                        ; For switching, the first bit of CR0,
    or eax, 0x1                         ; a control register, must be set
    mov cr0, eax

    jmp CODE_SEG:initialise_pm          ; Make a far jump to our 32-bit code. This forces the CPU
                                        ; to flush its cache of pre-fetched instructions

[bits 32]
; Initialise the registers and the stack once in protected mode
initialise_pm:
    mov ax, DATA_SEG                    ; Since we are in PM, old segments have no longer a meaning
    mov ds, ax                          ; we must point our segment registers to the data selector defined in GDT
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000                    ; Stack is set far away
    mov esp, ebp

    call BEGIN_PM


