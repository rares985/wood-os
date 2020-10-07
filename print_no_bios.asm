; 32-bit print function
;
; Parameters:
;   EBX - address of string to be printed
;
; Print is performed using direct video memory addressing

[bits 32]
VIDEO_MEM   equ     0xB8000

print_no_bios:
    pusha
    mov edx, VIDEO_MEM

print_no_bios_loop:
    mov al, [ebx]           ; AL holds the character value (pointed to by EBX)
    mov ah, 0x0F            ; VGA attribute for white foreground, black background

    cmp al, 0               ; Exit condition (null terminator found)
    je print_no_bios_done

    mov [edx], ax           ; Store character + attribute in video memory
    add ebx, 1              ; Move to next character in string
    add edx, 2              ; Jump 2 bytes in video memory for each character
                            ; 1 byte is used for the character and 1 for the attributes
    jmp print_no_bios_loop

print_no_bios_done:
    popa
    ret

