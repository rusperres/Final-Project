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
.code
include PROCS.INC
include AUTH_P.INC
include LOGIN_P.INC
Main:
    set_font 1112h
    
    mov ax, @data
    mov ds, ax
    
    mov screen_number[0], 3 

    setcursor 0, 0
    bg 00h, 10000
    setcursor 0, 0
    bg 0fh, 10000

    setcursor 25, 45
    lea dx, add_loan
    call print
    setcursor 27, 45
    lea dx, update_loan
    call print
    setcursor 29, 45
    lea dx, delete_loan
    call print
    setcursor 31, 45
    lea dx, back
    call print
    mov user_display_props[2], 0
    
    xor bx, bx
    mov bl, loan_count_idx
    cmp loan_counts[bx], 0
    je NoLoansExist
    jne HomeChoice
    NoLoansExist:
        mov focus, 1
        call PaintAdd
    HomeChoice:
        cmp screen_number[0], 3
        jne HomeReturn
        mov loan_display_props[1], 25
        mov loan_display_props[0], 25
        call SelectUserLoans

        call DisplayLoans
        xor ax, ax
        call WaitArrowKey
        cmp al, 0dh
        je HomeEnterPressed
        cmp al, 0
        jne HomeChoice
        cmp ah, 48h
        je HomeCallUp
        cmp ah, 50h
        je HomeCallDown
        cmp ah, 4bh 
        je HomeCallLeft
        cmp ah, 4dh
        je HomeCallRight
        jmp HomeChoice
    HomeCallUp:
        call HomeUp
        jmp HomeChoice
    HomeCallDown:
        call HomeDown
        jmp HomeChoice
    HomeCallLeft:
        mov focus, 0
        call PaintNone
        jmp HomeChoice
    HomeCallRight:
        mov focus, 1
        call HomeRight
        jmp HomeChoice
    HomeEnterPressed:
        setcursor 0, 0
        call HomeOnClick
        jmp HomeChoice
    HomeReturn:
Done:
    setcursor 48, 79
    mov ah, 4ch
    int 21h
HomeOnClick proc
    cmp focus, 1
    jne HomeOnClickDone
    cmp selected_option, 0
    je HomeOnClickCallAdd
    HomeOnClickCallAdd:
        call HomeAdd
        jmp HomeOnClickDone
    HomeOnClickDone:
    ret
HomeOnClick endp
SelectUserLoans proc
    xor ax, ax
    mov al, user_display_props[2] ; user index
    shl ax, 1                     ; WORD index

    ; select loan table
    mov bx, ax
    mov ax, loan_tables[bx]
    mov current_loans_ptr, ax

    ; select loan count
    xor ax, ax
    mov al, user_display_props[2]
    mov loan_count_idx, al

    xor ax, ax
    xor bx, bx
    ret
SelectUserLoans endp
DisplayLoan proc
    mov ax, TYPE Loan
    mul si
    mov di, current_loans_ptr
    add di, ax
    lea dx, [di+1]
    call print
    ret
DisplayLoan endp
HomeAdd proc
    mov string_buffer[0], 36
    mov string_buffer[1], 0
    mov string_buffer[2], 40
    mov string_buffer[3], 20
    call CenteredStringScan
    mov si, OFFSET string_buffer + 4
    ; --- get base of loan table ---
    xor bx, bx
    mov bl, loan_count_idx      ; index into loan_tables
    mov di, current_loans_ptr                  ; DI = base address of current loan table

    ; --- compute offset for next loan ---
    xor bx, bx
    mov bl, loan_count_idx
    mov al, loan_counts[bx] ; number of existing loans
    mov ah, 0
    mov cl, TYPE Loan
    mul cl                        ; AX = offset in bytes to next loan
    add di, ax                    ; DI = address of next loan
    add di, 1                     ; skip ID field (optional)
    
    ; --- setup ES ---
    mov ax, ds
    mov es, ax
    call CopyString

; increase loan_count
    xor bx, bx
    mov bl, loan_count_idx
    inc loan_counts[bx]
    setcursor 20, 32
    bg 00h, 16

    

    ret
HomeAdd endp
HomeRight proc
    mov focus, 1   
    cmp selected_option, 0
    je HomeRightCallPaintAdd
    cmp selected_option, 1
    je HomeRightCallPaintUpdate
    cmp selected_option, 2
    je HomeRightCallPaintDelete
    cmp selected_option, 3
    je HomeRightCallPaintBack
    HomeRightCallPaintAdd:
        call PaintAdd
        jmp HomeRightDone
    HomeRightCallPaintUpdate:
        call PaintUpdate
        jmp HomeRightDone
    HomeRightCallPaintDelete:
        call PaintDelete
        jmp HomeRightDone
    HomeRightCallPaintBack:
        call PaintBack
        jmp HomeRightDone

    HomeRightDone:
    ret
HomeRight endp
HomeDown proc
    cmp focus[0], 0
    je HomeLoansDown
    jne CallHomeOptionsDown
    CallHomeOptionsDown:
        call HomeOptionsDown
        jmp HomeDownDone
    HomeLoansDown:
        xor ax, ax
        xor bx, bx
        mov bl, loan_count_idx
        mov al, loan_counts[bx]
        dec al
        cmp loan_display_props[2], al
        je HomeDownDone
        inc loan_display_props[2]
    HomeDownDone:
    ret
HomeDown endp
HomeUp proc
    cmp focus[0], 0 ; if loans are focused on
    je HomeLoansUp ; goto LoansUp
    jne CallHomeOptionsUp
    CallHomeOptionsUp:
        call HomeOptionsUp
        jmp HomeUpDone
    HomeLoansUp:
        cmp loan_display_props[2], 0
        je HomeUpDone
        dec loan_display_props[2]
    HomeUpDone:
        ret
HomeUp endp
HomeOptionsDown proc
    cmp selected_option, 3
    je HomeOptionsDownDone
    inc selected_option
    HomeOptionsDownPaint:
        cmp selected_option, 0
        je DownCallPaintAdd
        cmp selected_option, 1
        je DownCallPaintUpdate
        cmp selected_option, 2
        je DownCallPaintDelete
        cmp selected_option, 3
        je DownCallPaintBack
        DownCallPaintAdd:
            call PaintAdd
            jmp HomeOptionsDownDone
        DownCallPaintUpdate:
            call PaintUpdate
            jmp HomeOptionsDownDone
        DownCallPaintDelete:
            call PaintDelete
            jmp HomeOptionsDownDone
        DownCallPaintBack:
            call PaintBack
            jmp HomeOptionsDownDone
    HomeOptionsDownDone:
    ret
HomeOptionsDown endp
HomeOptionsUp proc
    cmp selected_option, 0
    je HomeOptionsUpDone  ; skip if zero
    dec selected_option
    HomeOptionsUpPaint:
        cmp selected_option, 0
        je CallPaintAdd
        cmp selected_option, 1
        je CallPaintUpdate
        cmp selected_option, 2
        je CallPaintDelete
        cmp selected_option, 3
        je CallPaintBack
        CallPaintAdd:
            call PaintAdd
            jmp HomeOptionsUpDone
        CallPaintUpdate:
            call PaintUpdate
            jmp HomeOptionsUpDone
        CallPaintDelete:
            call PaintDelete
            jmp HomeOptionsUpDone
        CallPaintBack:
            call PaintBack
            jmp HomeOptionsUpDone
    HomeOptionsUpDone:
    ret
HomeOptionsUp endp

DisplayLoans proc
    xor si, si
    xor di, di
    DisplayLoansLoop:
        xor ax, ax
        xor bx, bx
        mov bl, loan_count_idx
        mov al, loan_counts[bx]
        cmp si, ax
        jae DisplayLoansDone
        setcursor loan_display_props[0], loan_display_props[1]
        xor ax, ax
        mov al, loan_display_props[2]
        cmp si, ax
        jne UnPaintLoan
        cmp focus, 0
        jne UnpaintLoan
        bg 7fh, 16
        jmp ProceedDisplayLoan
    UnpaintLoan:
        bg 0fh, 16
    ProceedDisplayLoan:
        call DisplayLoan
        add loan_display_props[0], 2
        inc si
        jmp DisplayLoansLoop
    DisplayLoansDone:
        ret
DisplayLoans endp
PaintNone proc
    setcursor 25, 45
    bg 0fh, 6
    lea dx, add_loan
    call print
    setcursor 27, 45
    lea dx, update_loan
    bg 0fh, 6
    call print
    setcursor 29, 45
    bg 0fh, 6
    lea dx, delete_loan
    call print
    setcursor 31, 45
    bg 0fh, 6
    lea dx, back
    call print
    ret
PaintNone endp
PaintAdd proc
    setcursor 25, 45
    bg 7fh, 6
    lea dx, add_loan
    call print
    setcursor 27, 45
    lea dx, update_loan
    bg 0fh, 6
    call print
    setcursor 29, 45
    bg 0fh, 6
    lea dx, delete_loan
    call print
    setcursor 31, 45
    bg 0fh, 6
    lea dx, back
    call print
    ret
PaintAdd endp
PaintUpdate proc
    setcursor 25, 45
    bg 0fh, 6
    lea dx, add_loan
    call print
    setcursor 27, 45
    bg 7fh, 6
    lea dx, update_loan
    call print
    setcursor 29, 45
    bg 0fh, 6
    lea dx, delete_loan
    call print
    setcursor 31, 45
    bg 0fh, 6
    lea dx, back
    call print
    ret
PaintUpdate endp
PaintDelete proc
    setcursor 25, 45
    bg 0fh, 6
    lea dx, add_loan
    call print
    setcursor 27, 45
    bg 0fh, 6
    lea dx, update_loan
    call print
    setcursor 29, 45
    bg 7fh, 6
    lea dx, delete_loan
    call print
    setcursor 31, 45
    bg 0fh, 6
    lea dx, back
    call print
    ret
PaintDelete endp
PaintBack proc
    setcursor 25, 45
    bg 0fh, 6
    lea dx, add_loan
    call print
    setcursor 27, 45
    bg 0fh, 6
    lea dx, update_loan
    call print
    setcursor 29, 45
    bg 0fh, 6
    lea dx, delete_loan
    call print
    setcursor 31, 45
    bg 7fh, 6
    lea dx, back
    call print
    ret
PaintBack endp
end Main
    

