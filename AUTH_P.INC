Auth proc
    setcursor 0, 0
    bg 0Fh, 10000
    setcursor 15, 0
    mov login_button[0], 1
    mov register_button[0], 0
    mov login_button[1], 7fh
    mov register_button[1], 0fh
    lea dx, logo
    call print
    call SetAuthState

    setcursor 48, 1
    lea dx, inst_arrow
    call print

;   Choose Login or Register
@@Choice:
    xor ax, ax
    call WaitArrowKey 
    
    cmp al, 0dh
    je @@EnterPressed
   
    cmp al, 0
    jne @@Choice

    cmp ah, 48h
    je @@CallUp
    cmp ah, 50h
    je @@CallDown
    jmp @@Choice
@@CallUp:
    call AuthUp
    setcursor 50, 79
    jmp @@Choice
@@CallDown:
    call AuthDown 
    setcursor 50, 79
    jmp @@Choice
@@EnterPressed:
    setcursor 0, 0
    call AuthOnClick
    ret
Auth endp
WaitArrowKey proc
    xor ah, ah
    int 16h
    ret
WaitArrowKey endp
SetAuthState proc
    setcursor 30, 36
    bg login_button[1], 8
    lea dx, login_button[2]
    call print
    setcursor 31, 36
    bg register_button[1], 8
    lea dx, register_button[2]
    call print
    setcursor 50, 79
    ret
SetAuthState endp
AuthUp proc
    mov login_button[0], 1
    mov login_button[1], 7fh

    mov register_button[0], 0
    mov register_button[1], 0fh
    call SetAuthState
    ret
AuthUp endp
AuthDown proc
    mov login_button[0], 0
    mov login_button[1], 0fh

    mov register_button[0], 1
    mov register_button[1], 7fh
    call SetAuthState
    ret
AuthDown endp
AuthOnClick proc
    cmp login_button[0], 1
    jne @@EnterRegister
    mov login_button[1], 4fh
    call SetAuthState
    delay 200
    mov login_button[1], 7fh
    call SetAuthState
    delay 200
    jmp @@EndClick
    @@EnterRegister:
        mov register_button[1], 4fh
        call SetAuthState
        delay 200
        mov register_button[1], 7fh
        call SetAuthState
        delay 200
        call RegisterOnClick
    @@EndClick:
        ret
AuthOnClick endp
RegisterOnClick proc
    mov string_buffer[2], 40
    mov string_buffer[0], 36
    mov string_buffer[1], 0
    setcursor 36,19 
    lea dx, register_prompt 
    call print 
    mov string_buffer[3], 40
    call CenteredStringScan
    ret
RegisterOnClick endp
