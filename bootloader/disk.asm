HPC equ 2
SPT equ 18
; Function for reading from disk. It has built-in a LBA->CHS address
; convertor. This is to avoid problems when loading the kernel, in
; case we need to read more than a track at once, since for example,
; starting at (0, 0, 19) would make BIOS issue an error instead of
; wrapping around to (0, 1, 1)
; Conversion formulas are given below:
;   C = LBA / (HPC * SPT)
;   H = (LBA / SPT) % HPC
;   S = (LBA % SPT) + 1
;
; Function parameters:
;       DL - Drive to read from
;       AL - how many sectors to read
;       ECX - LBA address
;       ES:BX - pointer where to read the result
;


disk_load:
    pusha
    push ax             ; Store how many sectors to read on stack (EAX will be altered)
    push eax            ; Store how many sectors to read on stack (EAX will be altered)
    push ebx            ; Store the location pointer on stack (EBX will be altered)
    push edx            ; Store drive to read from on stack (EDX will be altered)

    mov ebx, ecx        ; Store the LBA address in EBX, as this register
                        ; is not altered by the mul or div operations
                        
                        ; 1. First perform the operation LBA / SPT.
                        ; This is useful because the mul operation in x86
                        ; provides both the result and the remainder of
                        ; the operation, and we can use them for calculating
                        ; H and S.

                        ; The div operation in x86 performs the division (EDX:EAX) / ECX.
    mov edx, 0          ; 
    mov eax, ebx        ; EDX:EAX = 0:LBA.
    mov ecx, SPT
    div ecx             ; Perform the actual division by SPT.

                        ; Remainder (LBA % SPT) is stored in EDX.
    add edx, 1          ; EDX = (LBA % SPT) + 1 = S.
    push edx            ; Store the S value on stack so we can recall it later


                        ; 2. Let's now calculate the H value.
                        ; Recall that EAX = LBA / SPT from previous division operation
                        ; All we need to do is divide the result from previous operation
                        ; by HPC. 
    mov edx, 0
    mov ecx, HPC
    div ecx             ; (LBA / SPT) / HPC.
                        ; EDX = EDX:EAX % ECX = (LBA / SPT) % HPC = H
    push edx            ; Store the H value on stack so we can recall it alter

                        ; 3. Now let's calculate the C value.
                        ; The mul operation in x86 performs a multiplication of
                        ; EAX by a value with the result being stored in EDX:EAX.
                        ; First we compute the value HPC * SPT.

    mov eax, HPC
    mov ecx, SPT
    mul ecx             ; EDX:EAX = HPC * SPT

    mov ecx, eax        ; ECX = HPC * SPT
    mov eax, ebx        ; EAX = LBA
    mov edx, 0
    div ecx             ; EAX = LBA / (HPC * SPT)
    push eax            ; Store the C value on stack so we can recall it later.

                        ; The interrupt 13h, ah=02h must have the registers set as follows:
    pop eax
    mov ch, al          ;       CH - Cylinder value (C)
    pop eax
    mov dh, al          ;       DH - Head value (H)
    pop eax
    mov cl, al          ;       CL - Sector value (S)
    pop eax
    mov dl, al          ;       DL - drive to read from (stored on stack at start)

    pop ebx             ;       BX - location pointer (stored on stack at start)
    pop eax             ;       AL - How many sectors to read (stored on stack at start)
    mov ah, 0x02        ;       AH - 02h (BIOS read sectors from drive function)




    int 0x13            ; Issue BIOS to perform the read
    jc disk_error       ; If errored, the carry bit will be set

    pop dx
    cmp dl, al          ; If AL (sectors read) != DL (sectors expected)
    jne disk_warn


disk_load_done:
    popa
    ret


disk_error:
    mov bx, DISK_ERR_MSG
    call print
    mov dh, ah              ; AH = error code, DH = disk which errored
    call print_hex
    jmp disk_load_done      ; hang in case of error


disk_warn:
    mov bx, EXPECTED_MSG
    call print
    call print_hex          ; DH - sectors expected
    mov bx, READ_MSG
    call print
    mov dh, al              ; AL - sectors read
    call print_hex
    jmp disk_load_done


DISK_ERR_MSG:
    db "Disk read error!", 0
READ_MSG:
    db "Read", 0
EXPECTED_MSG:
    db "Expected", 0