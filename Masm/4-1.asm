assume cs:codesg

    codesg segment

            mov ax, 20h
            mov ds, ax
            mov bl, 0
            mov cx, 64

    move:   mov ds:[bx], bl
            inc bl
            loop move
            mov ax, 4c00h
            int 21h

    codesg ends
    
    end