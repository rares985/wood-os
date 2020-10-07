; Ensures that we jump straight to the kernel's entry function
global _start           ; For avoiding linking issues, we have to define
_start:                 ; a _start label

[bits 32]               ; By now we are in protected mode, so we are using 32-bit instructions
[extern kernel_main]    ; Declare that we will be referencing the external symbol 'kernel_main',
                        ; so the linker can substitute the final address
call kernel_main        ; Invoke the function kernel_main() in our C kernel
jmp $                   ; Hang forever when we return from kernel