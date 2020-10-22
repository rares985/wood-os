HPC equ 2
SPT equ 18
; Function for reading from disk. It has built-in a LBA->CHS address
; convertor. This is to avoid problems when loading the kernel, in
; case we need to read more than a track at once, since for example,
; starting at (0, 0, 19) would make BIOS issue an error instead of
; wrapping around to (0, 1, 1).
; Conversion formulas are given below:
;   C = LBA / (HPC * SPT)
;   H = (LBA / SPT) % HPC
;   S = (LBA % SPT) + 1
;
; Function parameters:
;       DL - Drive to read from
;       DH - how many sectors to read
;       AX - LBA address
;       ES:BX - pointer where to read the result
disk_load:
    mov cl, 0           ; Initialize the counter

disk_load_loop:
    cmp cl, dh          ; Exit condition
    jge disk_load_done

    push ax             ; AX will have to be modified to satisfy
                        ; the parameters of the int13h

    push cx             ; lba2chs function trashes register CX
    push dx             ; lba2chs trashes register DX

    call lba2chs        ; Convert LBA address to CHS

    pop ax              ; Our stack top is the value of DX before being trashed.
                        ; This means that after the pop operation, AX will contain 
                        ; the drive in AH, and the sector count (how many sectors to read) in AL.
                        ; INT13H requires the drive to be stored in DL and the 
                        ; Head (H) value to be stored in DH. Since the head is placed
    mov dl, al          ; into DH by the lba2chs function, we can not perform a pop directly
                        ; into the dx register because that would overwrite the H value, so we 
                        ; are using AX as a temporary variable.

    push ax             ; Again store the value of AX (aka DX), since we will need the sector count
                        ; and the AX will be trashed both by us and by the INT13h.

                        ; Parameters required by INT13H:
    mov ah, 0x02        ; AH - 02h (BIOS Read Sector function)
    mov al, 0x01        ; AL - Sectors To Read Count (1 at a time)
                        ; CH - Cylinder (C) - placed by lba2chs function
                        ; CL - Sector (S) - placed by lba2chs function
                        ; DH - Head (H) - placed by lba2chs function
                        ; DL - drive - placed by us
                        ; ES:BX - destination pointer (placed by callee of this function)

    int 0x13
    jc disk_error       ; If errored, carry bit will be set

    pop ax              ; Restore the sector count
    mov dh, al          ; Exit condition requires sector count to be stored in dh

    pop cx              ; Restore the counter
    add cl, 1           ; Increment the counter of read sectors

    pop ax              ; Restore LBA address
    add ax, 1           ; Increment the LBA address (+1 sector)
    add bx, 512         ; Increment the BX pointer (+512 bytes)

    jmp disk_load_loop  ; Loop back

disk_load_done:
    ret


; Function which converts a  LBA address to CHS.
; Trashes register CX, DX.
;
; Input parameters:
;   AX - LBA address to be converted
; Output parameters:
;   CH:CL  - Cylinder:Sector (C:S)
;   DH     - Head value (H)

lba2chs:
    push ax             ; We will be trashing AX, but will restore it 
    push bx             ; We will be trashing BX, but will restore it

                        ; First perform the division LBA / SPT.
    mov dx, 0           ; x86 div operation performs the division (dx:ax)/cx,
                        ; storing the quotient in ax and the remainder in dx.
    mov cx, SPT         ; In our case, the division is (0:LBA) / SPT, 
    div cx              ; with LBA / SPT stored in ax, and LBA % SPT in dx.

    add dx, 1           ; S = (LBA % SPT) + 1
    push dx             ; Store the S value on stack so we do not worry
                        ; about trashing the register.

    mov dx, 0           ; (dx:ax) / cx = (0:(LBA / SPT)) / HPC
    mov cx, HPC         ; ax = LBA / SPT / HPC -> C value
    div cx              ; dx = (LBA / SPT) % HPC -> H value

    push dx             ; Store H value on stack
    push ax             ; Store C value on stack

    pop bx              ; Use BX as temp variable (BX = C)
    mov ch, bl          ; CH = Cylinder (C)

    pop bx              ; BX = H
    mov dh, bl          ; DH = Head(H)

    pop bx              ; BX = S
    mov cl, bl          ; CL = Sector (S)

    pop bx              ; Restore BX
    pop ax              ; Restore AX
    ret


disk_error:
    mov bx, DISK_ERR_MSG
    call print
    mov dh, ah              ; AH = error code, DL = disk which errored
    call print_hex
    jmp $                   ; hang in case of error

DISK_ERR_MSG:
    db "Disk read error!", 0