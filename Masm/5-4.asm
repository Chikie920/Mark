assume cs:code

data1 segment

    db 1, 2, 3, 4, 5, 6, 7, 8

data1 ends

data2 segment

    db 1, 2, 3, 4, 5, 6, 7, 8

data2 ends

data3 segment

    db 0, 0, 0, 0, 0, 0, 0, 0

data3 ends

code segment

start:  mov ax, data1
        mov ds, ax
        mov ax, data3
        mov es, ax
        mov bx, 0
        mov cx, 8

        move_option: mov al, [bx]
                     mov es:[bx], al
                     inc bx
                     loop move_option
                        
                     mov ax, data2
                     mov ds, ax
                     mov bx, 0
                     mov cx, 8

        add_option: mov al, ds:[bx]
                    add es:[bx], al
                    inc bx
                    loop add_option

        mov ax, 4c00h
        int 21h


code ends

end start