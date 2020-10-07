; 16-bit print function
;
; Parameters:
;   BX - address of string to be printed
;
; Print is performed with the help of a BIOS function (interrupt 0x10)

print:
    pusha
    mov ah, 0x0e        ; Tell BIOS to output in tele-type mode

print_char:
    mov al, [bx]        ; Move first character of string into AL for printing
    cmp al, 0           ; Check exit condition - null terminator found
    je done

    int 0x10            ; Print the character stored in AL

    add bx, 1           ; Go to the next character in the string
    jmp print_char      ; And repeat

done:
    popa
    ret
