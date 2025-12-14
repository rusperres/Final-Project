   add_loan db "ADD$"
   update_loan db "UPDATE$"
   delete_loan db "DELETE$"
    currency db "Php $"

User struc
    id db ?
    username db 16 dup('$') ; 15 chars
User ends
users User \
    <0, "Jairus$">, \
    9 dup (<>)
user_count dw 1
user_display_props db 0, 0, 0, 0
; 0 - row
; 1 - column
; 2 - selected
; 3 - back - selected
login_logo db "                         _     _____ _____ _____ _   _", 0dh, 0ah,   \
              "                        | |   |  _  |  __ \_   _| \ | |", 0dh, 0ah,   \
              "                        | |   | | | | |  \/ | | |  \| |", 0dh, 0ah,   \
              "                        | |   | | | | | __  | | | . ` |", 0dh, 0ah,   \
              "                        | |___\ \_/ / |_\ \_| |_| |\  |", 0dh, 0ah,   \
              "                        \_____/\___/ \____/\___/\_| \_/$"
 home_logo db "            __     __                _                           ", 0dh, 0ah,  \
              "            \ \   / /               | |                          ", 0dh, 0ah,  \
              "             \ \_/ /__  _   _ _ __  | |     ___   __ _ _ __  ___ ", 0dh, 0ah,  \
              "              \   / _ \| | | | '__| | |    / _ \ / _` | '_ \/ __|", 0dh, 0ah,  \
              "               | | (_) | |_| | |    | |___| (_) | (_| | | | \__ \", 0dh, 0ah,  \
              "               |_|\___/ \__,_|_|    |______\___/ \__,_|_| |_|___/$"
                                                      
                                                      

selected_user db 0                  
Loan struc
    id db ?
    amount db 16 dup('$')
Loan ends

focus db 0 
; 0 - list of loans
; 1 - options

selected_option dw 0
; 0 - add
; 1 - update
; 2 - delete
; 3 - back
loan_display_props db 0, 0, 0
; 0 - row
; 1 - column
; 2 - selected
; 3 - back - selected
loan_counts db 10, 0, 0, 0, 0, 0, 0, 0, 0, 0
loan_count_idx db 0
loans2 Loan 10 dup(<>)

loans1 Loan \
    <0, "11000$">, \
    <1, "26000$">, \
    <2, "5200$">,  \
    <3, "13000$">, \
    <4, "8000$">,  \
    <5, "31000$">, \
    <6, "19000$">, \
    <7, "9800$">,  \
    <8, "43000$">, \
    <9, "6500$">


loans3 Loan 10 dup(<>)
loans4 Loan 10 dup(<>)
loans5 Loan 10 dup(<>)
loans6 Loan 10 dup(<>)
loans7 Loan 10 dup(<>)
loans8 Loan 10 dup(<>)
loans9 Loan 10 dup(<>)
loans10 Loan 10 dup(<>)

; pointers to loan tables
loan_tables dw OFFSET loans1, OFFSET loans2, OFFSET loans3, OFFSET loans4, \
               OFFSET loans5, OFFSET loans6, OFFSET loans7, OFFSET loans8, \
               OFFSET loans9, OFFSET loans10

current_loans_ptr  dw ?

