; 16-bit print function for hex
;
; Parameters
;   DX - hex value to be printed
; 
; For examples, value 0x1234 will be used

print_hex:
    pusha
    mov ah, 0x0e            ; Tell BIOS to output in tele-type mode
    mov cx, 0               ; This is the index variable (such as i)


convert_char:
    cmp cx, 4               ; Exit condition (all 4 characters have been converted)
    je end

    mov ax, dx              ; AX is used as a working register
    and ax, 0x000F          ; Extract only last 4 bits (last letter)
    add al, 0x30            ; Add 0x30 (e.g: 9 becomes 0x39 = ASCII code of '9')
    cmp al, 0x39
    jle copy_char           ; If value is smaller than 39, copy char to destination string
    add al, 7               ; If value is greater than 39, then al is a hex letter and 7 needs to be added
                            ; ASCII code of 'A' minus ASCII code of '9' - 1 = 65 - 57 - 1 = 7


                            ; Calculate into BX the position where the character will be placed
                            ; 1st character will be placed at base + length - 1
                            ; 2nd character will be placed at base + length - 2
copy_char:
    mov bx, HEX_STRING + 5  ; Starting from end of string, go to its end
    sub bx, cx              ; Subtract the index
    mov [bx], al            ; Copy the character to the address pointed by BX
    ror dx, 4               ; 0x1234->0x4123->0x3412->0x2341->0x1234, so DX is left unaltered
    add cx, 1               ; Go to the next character
    jmp convert_char


end:
    mov bx, HEX_STRING      ; Move the string to BX, as required by print function
    call print

    popa
    ret

HEX_STRING:
    db '0x0000',0           ; Converted characters will be placed here
