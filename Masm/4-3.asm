assume cs:codesg

codesg segment

               mov  ax, 20h
               mov  ds, ax
               mov  ax, cs
               mov  es, ax
               mov  bx, 0
               mov  cx, 15h

        move:  mov  al, cs:[bx]
               mov  [bx], al
               inc  bx
               loop move
               mov  ax, 4c00h
               int  21h

codesg ends

    end

            
