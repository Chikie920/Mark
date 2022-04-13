assume cs:code

data segment

    db '1975','1976','1977','1978','1979','1980','1981','1982','1983','1984','1985'
    db '1986','1987','1988','1989','1990','1991','1992','1993','1994','1995'

    dd 16,22,382,1356,2390,8000,16000,24486,50065,97479,140417,197514,345980
    dd 590827,803530,1183000,1843000,2758000,3753000,4649000,5937000

    dw 3,7,9,13,28,38,130,220,476,778,1001,1442,2258,2793,4037,5635,8226
    dw 11542,14430,15257,17800

data ends

table segment

    db 21 dup ('year summ ne ?? ')

table ends

stack segment

    db 16 dup (0)

stack ends

code segment

    start:  mov ax, data
            mov ds, ax
            mov ax, table
            mov es, ax
            mov ax, stack
            mov ss, ax
            mov sp, 10h
            mov bx, 0
            mov cx, 15h
            mov si, 0
            mov di, 54h ; 收入相对于年份的偏移

            move_1: push [bx]
                    push[bx+2]
                    pop es:[2+si]
                    pop es:[si] ; 将年份写入

                    push [bx+di]
                    push [bx+2+di]
                    pop es:[7+si]
                    pop es:[5+si] ; 将收入写入

                    add bx, 4 ; 移动double word
                    add si, 10h ; 下一行
                    loop move_1

                    mov cx, 15h
                    mov bx, 0
                    mov si, 0

            move_2: push [bx+0a8h]
                    pop es:[0ah+si] ; 写入雇员数量

                    mov dx, es:[7+si]
                    mov ax, es:[5+si]
                    div word ptr es:[0ah+si] ; 计算人均收入

                    mov es:[0dh+si], ax

                    add si, 10h ; 下一行
                    add bx, 2 ; 移动word

                    loop move_2


            mov ax, 4c00h
            int 21h     

code ends

end start
