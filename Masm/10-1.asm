assume cs:code

data segment

    db 'Welcome to masm!', 0

data ends

stack segment

dw 8 dup(0)

stack ends

code segment

start: mov dh, 8 ; 行
       mov dl, 3 ; 列
       mov cl, 82h ; 颜色
       mov ax, data
       mov ds, ax
       mov si, 0
       call show_str
       mov ax, 4c00h
       int 21h

show_str: push cx ; 属性入栈
          mov al, 0ah
          mul dh
          add ax, 0b800h ; 第一行在屏幕外显示不出来，要从第二行开始
          mov es, ax ; 目的行地址
          mov al, 2
          dec dl
          mul dl
          mov bl, al
          mov bh, 0 ; 设置目的列地址

          move: mov cl, [si]
                mov ch, 0
                jcxz move_over ; cx为0则跳转
                mov es:[bx], cl ; 复制字符到目的地址
                pop cx
                mov es:[bx+1], cl ; 写入属性
                inc si
                add bx, 2
                push cx
                jmp short move
          move_over: pop cx ; 这里一定要记得把cx出栈，不然ret返回给ip的值为cx的值
                     ret

code ends

end start