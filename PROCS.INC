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

setcursor MACRO row, col
    mov ah, 02h
    mov dh, row
    mov dl, col
    int 10h
ENDM
bg MACRO attr, count
    mov ah, 09h
    mov al, ' '
    mov bl, attr
    mov cx, count
    int 10h
ENDM


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
Center endp


; =============================
;   Copies from string_buffer si to another target buffer di
; sample usage:
;   mov si, OFFSET string_buffer + 4  ; point to input string
;   mov ax, TYPE User
;   mov bx, user_count                          ; user index = 0
;   mul bx                             ; AX = offset
;   lea di, users
;   add di, ax
;   add di, 1
;   mov ax, ds
;   mov es, ax
;   call CopyString                    ; copy string into users[0].username
;   inc user_count

CopyString proc
    CopyLoop:
        lodsb
        stosb
        cmp al, '$'
        jne CopyLoop
    ret
CopyString endp
ReadString proc
    xor si, si
    mov si, 4
    ReadStringLoop:
        call RePrint
        mov ah, 01h
        int 21h
        cmp al, 0dh ; check if enter
        je ReadStringLoopDone
        cmp al, 08h ; check if delete
        jne ReadStringNoDelete
        cmp si, 4
        je ReadStringLoop   ; will not delete if si is 4
        mov string_buffer[si-1], '$' ; delete
        dec si
        dec string_buffer[1]
        call RePrint
        jmp ReadStringLoop
        ReadStringNoDelete:
            cmp si, 17
            je ReadStringLoop
            cmp al, 126 ; ascii upper bound
            ja ReadStringLoop
            cmp al, 32  ; ascii lower bound
            jb ReadStringLoop
            mov string_buffer[si], al
            mov string_buffer[si+1], '$'
            inc si
            inc string_buffer[1]
            jmp ReadStringLoop
            ReadStringLoopDone:
                mov string_buffer[si], '$'
                ret
ReadString endp
RePrint proc
    setcursor string_buffer[3], string_buffer[0]
    bg 00h, 15
    setcursor string_buffer[3], string_buffer[0]
    bg 0fh, 15
  
    lea dx, string_buffer[4]
    call print
    mov cl, string_buffer[0]
    add cl, string_buffer[1]
    setcursor string_buffer[3], cl
    ret
RePrint endp
ClearStringBuffer proc
    mov cx, 15
    xor si, si
    mov si, 4
    mov string_buffer[0], 0
    mov string_buffer[1], 0
    mov string_buffer[2], 0
    mov string_buffer[3], 0
    ClearStringBufferLoop:
        cmp si, 17
        je ClearStringDone
        mov string_buffer[si], '$'
        inc si
    ClearStringDone:    
    ret
ClearStringBuffer endp
