; File implements the GDT (Global Descriptor Table)
;
;
;
; This is necessary for switching to the 32-bit protected mode.


gdt_start:              ; Used in calculations

gdt_null:               ; Mandatory 8 bytes of 0x00
    dq 0x00

gdt_code:               ; Code segment descriptor
    ; base = 0x0
    ; limit = 0xFFFF
    ; flags1 (1 - present,  00 - privilege, 1 - descriptor) -> 1001b
    ; type flags (1 - code, 0 - conforming, 1 - readable,  0 - accessed) ->  1010b
    ; flag2 (1 - granularity, 1 - 32bit default, 0 - 64bit segment,  0 - AVL) -> 1100b
    dw 0xFFFF           ; Limit (bits 0-15)
    dw 0x00             ; Base (bits 0-15)
    db 0x00             ; Base (bits 16-23)
    db 10011010b        ; flags1, type flags
    db 11001111b        ; flags2, limit (bits 16-19)
    db 0x00             ; Base (bits 24-31)

gdt_data:               ; Data segment descriptor
    ; Same as code segment except for the type flags
    ; type flags (0 - code, 0 - expand down, 1 - writeable,  0 - accessed) ->  0010b
    dw 0xFFFF           ; Limit (bits 0-15)
    dw 0x0              ; Base (bits 0-15)
    db 0x0              ; Base (bits 16-23)
    db 10010010b        ; flags1, type flags
    db 11001111b        ; flags2, limit (bits 16-19)
    db 0x0              ; Base (bits 24-31)

gdt_end:                ; Used in calculations

gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; Size of the GDT, always 1 smaller than true size
    dd gdt_start                ; Start address of GDT

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
