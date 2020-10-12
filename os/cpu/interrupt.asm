; Defined in isr.c
[extern isr_handler]
[extern irq_handler]

; Common ISR stub
isr_common_stub:
    ; Step 1: Save CPU current state
    pusha                       ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax
    mov ax, ds                  ; Lower 16-bits of eax = ds.
    push eax                    ; save the data segment descriptor
    mov ax, 0x10                ; load the kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    push esp                    ; registers_t *regs

    ; Step 2: Call C-level handler
    cld
    call isr_handler

    ; Step 3: Restore CPU state
    pop eax
    pop eax
    mov ds, ax                  ; reload the original data segment descriptor
    mov es, ax
    mov fs, ax
    mov gs, ax
    popa                        ; Pops edi,esi,ebp...
    add esp, 8                  ; Cleans up the pushed error code and pushed ISR number
    iret                        ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP



; Common IRQ code. Identical to ISR code except for the 'call' 
; and the 'pop ebx'
irq_common_stub:
    pusha 
    mov ax, ds
    push eax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    push esp
    cld
    call irq_handler ; Different than the ISR code
    pop ebx  ; Different than the ISR code
    pop ebx;
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx
    popa
    add esp, 8
    iret 

; This macro creates a stub for an IRQ - the first parameter is
; the IRQ number, the second is the ISR number it is remapped to.
%macro IRQ 2
    global irq%1
    irq%1:
        push byte %1
        push byte %2
        jmp irq_common_stub
        ret
%endmacro

%macro ISR_NOERRCODE 1  ; define a macro, taking one parameter
    global isr%1        ; %1 accesses the first parameter.
    isr%1:
        push byte 0
        push byte %1
        jmp isr_common_stub
        ret
%endmacro

%macro ISR_ERRCODE 1
    global isr%1
    isr%1:
        push byte %1
        jmp isr_common_stub
        ret
%endmacro


ISR_NOERRCODE   0
ISR_NOERRCODE   1
ISR_NOERRCODE   2
ISR_NOERRCODE   3
ISR_NOERRCODE   4
ISR_NOERRCODE   5
ISR_NOERRCODE   6
ISR_NOERRCODE   7
ISR_NOERRCODE   8       ; Pushes always error code 0
ISR_NOERRCODE   9
ISR_ERRCODE     10      ; Also pushes an error code to stack
ISR_ERRCODE     11      ; Also pushes an error code to stack
ISR_ERRCODE     12      ; Also pushes an error code to stack
ISR_ERRCODE     13      ; Also pushes an error code to stack
ISR_ERRCODE     14      ; Also pushes an error code to stack
ISR_NOERRCODE   15
ISR_NOERRCODE   16
ISR_ERRCODE     17      ; Also pushes an error code to stack
ISR_NOERRCODE   18
ISR_NOERRCODE   19
ISR_NOERRCODE   20
ISR_NOERRCODE   21
ISR_NOERRCODE   22
ISR_NOERRCODE   23
ISR_NOERRCODE   24
ISR_NOERRCODE   25
ISR_NOERRCODE   26
ISR_NOERRCODE   27
ISR_NOERRCODE   28
ISR_NOERRCODE   29
ISR_ERRCODE     30      ; Also pushes an error code to stack
ISR_NOERRCODE   31

IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47
