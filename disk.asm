; Function which loads disk sectors.
; 
; Parameters:
;   DX - how many sectors to read
;   DL - drive from which to read
;
; Result will be read into ES:BX

disk_load:
    pusha
    push dx         ; Store DX on stack so we can later
                    ; recall

    mov ah, 0x02    ; BIOS read sector function
    mov al, dh      ; Read function requires the number of sectors to be stored in AL
    mov ch, 0x00    ; Read function requires the cylinder stored in CH (in our case, 0)
    mov dh, 0x00    ; Read function requires the head stored in DH (in our case, 0)
    mov cl, 0x02    ; Start reading from sector 2 (after the boot sector)

    int 0x13        ; Issue BIOS to perform the read

    jc disk_error   ; If errored, the carry bit will be set

    pop dx          ; Restore DX from stack
    cmp dh, al      ; If AL (sectors read) != DH (sectors expected)
    jne disk_error  ; display error message

    popa
    ret


disk_error:
    mov bx, DISK_ERR_MSG
    call print
    mov dh, ah              ; AH = error code, DH = disk which errored
    call print_hex


DISK_ERR_MSG:
    db "Disk read error!", 0