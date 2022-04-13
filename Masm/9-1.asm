; 该程序不能在debug里面调试哦，显存缓冲区会一直被刷新，应该直接编译运行

assume cs:code, ds:data, ss:stack

data segment

db 3 dup ('welcome to masm!')
db 82h, 24h, 71h

data ends

stack segment

dw 2 dup (0)

stack ends

code segment

start:  mov ax, data
        mov ds, ax ; 设置数据段
        mov ax, stack
        mov ss, ax
        mov sp, 4 ; 设置栈段
        mov ax, 0b80ah ; 若偏移从0开始则在屏幕第一行之上，无法显示
        mov es, ax ; 设置目标地址
        mov cx, 3 ; 外层循环次数
        mov bx, 0
        mov si, 30h ; 颜色偏移

        move: push ax
              push cx ; 外层循环次数入栈
              mov cx, 10h ; 设置内层循环
              mov di, 0
            move_r: mov al, ds:[bx]
                    mov es:[di], al ; 数据段字符字节写入目标地址低字节处
                    mov al, ds:[si]
                    mov es:[di+1], al ; 属性字段写入目标地址高低字节处
                    inc bx ; 下一字符
                    add di, 2 ; 下一字段
                    loop move_r

                    add si, 1 ; 下一个属性
                    pop cx ; 外层循环次数出栈
                    pop ax ; 目标地址出栈
                    add ax, 0ah
                    mov es, ax ; 下一行输出地址
              loop move

        mov ax, 4c00h
        int 21h

code ends

end start