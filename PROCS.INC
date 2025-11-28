; ------------------------
; SetScreen MACRO
; mode - 8-bit screen mode number
; 25 lines = 1114h
; 28 lines = 1111h
; 50 lines = 1112h
; ------------------------
set_font macro font
    mov ax, font      ; BIOS function: set font
    mov bx, 0000h
    int 10h           
endm


print proc
    mov ah, 09h
    int 21h
    ret
print endp

; Macro with parameter in milliseconds
delay MACRO ms
    mov cx, ms
    call DelayProc
ENDM

; Delay by milliseconds (approximately)
; Input: cx = milliseconds to delay
DelayProc proc
    push ax
    push bx
    push cx
    push dx
    
    ; Convert milliseconds to microseconds (ms * 1000)
    mov ax, cx
    mov bx, 1000
    mul bx              ; dx:ax = milliseconds * 1000
    mov cx, dx
    mov dx, ax          ; cx:dx = microseconds
    
    ; Use BIOS wait function
    mov ah, 86h
    int 15h             ; Wait cx:dx microseconds
    
    pop dx
    pop cx
    pop bx
    pop ax
    ret
DelayProc endp
CenteredStringScan proc 
    xor si, si 
    mov si, 4
    EnterStringLoop: 
        
        call Center
        mov ah, 01h 
        int 21h  
        cmp al, 0dh                     ; check if enter 
        je EnterStringLoopDone 
        cmp al, 08h                     ; check if delete
        jne EnterStringNoDelete
        cmp si, 4
        je EnterStringLoop
        mov string_buffer[si-1], '$'
        dec si
        dec string_buffer[1]
        call Center
        jmp EnterStringLoop 
        EnterStringNoDelete:  
            cmp si, 17
            je EnterStringLoop
            cmp al, 126
            ja EnterStringLoop
            cmp al, 32
            jb EnterStringLoop
            mov string_buffer[si], al 
            mov string_buffer[si+1], '$' 
            inc si 
            inc string_buffer[1] 
            jmp EnterStringLoop 
            EnterStringLoopDone: 
                mov string_buffer[si], '$' 
                ret 
CenteredStringScan endp
Center proc 
    mov ch, string_buffer[2] 
    mov cl, string_buffer[1] 
    shr cl, 1 
    sub ch, cl 
    mov string_buffer[0],ch 
    setcursor string_buffer[3], 0 
    bg 00h, 79 
    setcursor string_buffer[3], string_buffer[0] 
    bg 0fh, 15 
    lea dx, string_buffer[4] 
    call print 
    mov cl, string_buffer[0] 
    add cl, string_buffer[1] 
    setcursor string_buffer[3], cl 
    ret
endp
