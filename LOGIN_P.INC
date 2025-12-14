Login proc
    mov user_display_props[2], 0
    mov user_display_props[3], 0
    setcursor 0, 0

    bg 00h, 10000
    setcursor 0, 0
    bg 0fh, 10000
  
    setcursor 15, 0
    lea dx, login_logo
    call print
    setcursor 48, 75
    lea dx, back
    call print
    LoginChoice:      
        cmp screen_number[0], 2
        jne LoginReturn
        mov user_display_props[1], 25
        mov user_display_props[0], 32
        call DisplayUsers
        xor ax, ax
        call WaitArrowKey
        cmp al, 0dh
        je LoginEnterPressed

        cmp al, 0
        jne LoginChoice

        cmp ah, 48h
        je LoginCallUp
        cmp ah, 50h
        je LoginCallDown
        jmp LoginChoice
    LoginCallUp:
        call LoginUp
        jmp LoginChoice
    LoginCallDown:
        call LoginDown
        jmp LoginChoice
    LoginEnterPressed:
        setcursor 0, 0
        call LoginOnClick
        mov screen_number[0], 1
    LoginReturn:
    ret
Login endp
LoginUp proc
    cmp user_display_props[3], 1
    jne SkipBackUnselect
    setcursor 48, 75
    bg 0fh, 4
    setcursor 48, 75
    lea dx, back
    call print
    mov user_display_props[3], 0
    jmp LoginUpSkip

    SkipBackUnselect:
    cmp user_display_props[2], 0    ; if selected == 0
    je LoginUpSkip ; goto skip up
    LoginUserUp:    ; else decrement
        dec user_display_props[2]
    LoginUpSkip:
        ret
LoginUp endp
LoginDown proc
    mov cx, user_count
    dec cx
    cmp user_display_props[2], cl
    je GotoBack
    inc user_display_props[2]
    jmp LoginDownDone
    GotoBack:
        mov user_display_props[3], 1
        setcursor 48, 75
        bg 7fh, 4
        setcursor 48, 75
        lea dx, back
        call print
LoginDownDone:
        ret
LoginDown endp
LoginOnClick proc
    cmp user_display_props[3], 1
    jne DontClickBack
    setcursor 48, 75
    bg 4fh, 4
    setcursor 48, 75
    lea dx, back
    call print
    delay 200
    setcursor 48, 75
    bg 7fh, 4
    setcursor 48, 75
    lea dx, back
    call print
    mov screen_number[0], 1
    ret
    DontClickBack:
    mov cl, user_display_props[2]
    mov si, cx
    shl cl, 1
    mov user_display_props[1], 25
    add user_display_props[1], cl
    mov user_display_props[0], 32
    setcursor user_display_props[1], user_display_props[0]
    bg 4fh, 16
    call DisplayUser
    delay 200

    mov user_display_props[1], 25
    add user_display_props[1], cl
    mov user_display_props[0], 32
    setcursor user_display_props[1], user_display_props[0]
    bg 7fh, 16
    call DisplayUser
    ret
LoginOnClick endp
DisplayUsers proc
    mov cx, user_count
    xor si, si
    xor di, di
    DisplayUsersLoop:
        cmp si, user_count
        jae DisplayUsersDone
        setcursor user_display_props[1], user_display_props[0]
        xor ax, ax
        mov al, user_display_props[2]
        cmp si, ax
        jne UnpaintUser
        cmp user_display_props[3], 1
        je UnpaintUser
        bg 7fh, 16
        jmp ProceedDisplayUser
    UnpaintUser:
        bg 0fh, 16
    ProceedDisplayUser:
        call DisplayUser
        inc user_display_props[1]
        
        inc user_display_props[1]
        inc si
        jmp DisplayUsersLoop
    DisplayUsersDone:
        ret
DisplayUsers endp
DisplayUser proc
    mov ax, TYPE User
    mul si
    lea di, users
    add di, ax

    lea dx, [di+1]
    call print
    ret
DisplayUser endp

