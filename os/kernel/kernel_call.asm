[bits 32]
[extern kernel_main]        ; Declare that we will be referencing the external symbol 'kernel_main',
[global _start]             ; For avoiding linking issues, we have to define
_start:                     ; a _start label
                            ; so the linker can substitute the final address
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    call kernel_main        ; Invoke the function kernel_main() in our C kernel
    jmp $                   ; Hang forever when we return from kernel