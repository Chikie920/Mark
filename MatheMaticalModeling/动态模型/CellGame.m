clear
clc

n = 200; %元胞网格大小

p = 0.1;

contain = rand(n)<p; %初始细胞
% imagesc(cat(3, contain, zeros(n), zeros(n)));

cells = ones(n+2);

cells(2:end-1, 2:end-1) = contain;

while 1
    for i = 2:201
        for j = 2:201
            counts = cells(i-1, j-1)+cells(i-1, j)+cells(i-1, j+1)+cells(i, j-1)+cells(i, j+1)+cells(i+1, j-1)+cells(i+1, j)+cells(i+1, j+1);
            if(cells(i, j)&&(counts==2||counts==3))
            else
                cells(i, j)=0;
                if(counts==3)
                    cells(i, j)=1;
                end
            end
        end
    end
    pause(0.1);
    imagesc(cat(3, cells, zeros(n+2), zeros(n+2)));
    drawnow
end