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
.model small
.stack 100h
.data
    include DB.INC
    screen_number db 0, 0
    ; 0 - splash
    ; 1 - Auth
    ; 2 - Login
    ; 3 - Register
    string_buffer db 0, 0, 0, 0, "               $"
    ; 0 - start
    ; 1 - size
    ; 2 - center
    ; 3 - y
    user1 User <0, "Jairus$", 10000, 100, 0, "Owner$">
    include AUTH_D.INC 
    temp_login db "This is the login screen. Under construction :($"
   temp_register db "This is the register screen. Under construction :($"

.code
include PROCS.INC
include AUTH_P.INC
Main:
    set_font 1112h
    
    mov ax, @data
    mov ds, ax
    call Auth
    setcursor 0, 0
    bg 00h, 10000
    setcursor 0, 0
    bg 07h, 10000
    setcursor 20, 5
    
    cmp login_button[0], 1
    jne @@CallRegister
    lea dx, temp_login
    call print
    jmp Done
    @@CallRegister:
        lea dx, temp_register
        call print

Done:
    setcursor 50, 79
    mov ah, 4ch
    int 21h
end Main
    
