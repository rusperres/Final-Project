 .model small
.stack 100h
.data
    include DB.INC
    include GEN_D.INC
   include AUTH_D.INC 
   back db "BACK$"
   add_loan db "ADD$"
   update_loan db "UPDATE$"
   delete_loan db "DELETE$"
    currency db "Php $"
   
.code
include PROCS.INC
include AUTH_P.INC
include LOGIN_P.INC
include HOME_P.INC
Main:
    set_font 1112h
    
    mov ax, @data
    mov ds, ax
    call Home   
Done:
    setcursor 48, 79
    mov ah, 4ch
    int 21h
end Main
    

