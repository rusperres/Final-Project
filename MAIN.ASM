.model small 
.stack 100h
.data
    include DB.INC
    include GEN_D.INC
    include AUTH_D.INC
    back db "BACK$"
    temp_login db "This is the login screen. Under construction :($"
   temp_register db "This is the register screen. Under construction :($"
    
.code
include PROCS.INC
include AUTH_P.INC
include LOGIN_P.INC
include HOME_P.INC
Main:
    set_font 1112h
    
    mov ax, @data
    mov ds, ax
    mov screen_number[0], 1
    MainLoop:
        cmp screen_number[0], 1
        je CallAuth
        cmp screen_number[0], 2
        je CallLogin
        cmp screen_number[0], 3
        je CallHome
        CallAuth:
            call Auth
            jmp MainLoop
        CallLogin:
            call Login
            jmp MainLoop
        CallHome:
            call Home
            jmp MainLoop
Done:
    setcursor 50, 79
    mov ah, 4ch
    int 21h
end Main
    
