assume cs:code, ds:data, ss:stack

data segment

    dw 1, 2, 3, 4, 5, 6, 7, 8, 9, 0ah, 0bh, 0ch, 0dh, 0eh, 0fh, 0ffh

data ends

stack segment

    dw 0, 0, 0, 0, 0, 0, 0, 0

stack ends

code segment

start:  mov ax, data
        mov ds, ax
        mov ax, stack
        mov ss, ax
        mov sp, 16
        mov bx, 0
        mov cx, 8

        move:   push [bx]
                add bx, 2
                loop move

        mov ax, 4c00h
        int 21h

code ends

end start

