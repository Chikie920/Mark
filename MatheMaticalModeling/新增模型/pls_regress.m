clear
clc

load linnerud;

mu = mean(linnerud);
sig = std(linnerud);

linnerud = zscore(linnerud);

X = linnerud(:, [1:3]);
Y = linnerud(:, [4:end]);

n = size(X, 2);
m = size(Y, 2);

[XL,YL,XS,YS,beta,PCTVAR] = plsregress(X, Y);
fprintf('X主成分方差贡献率的累加序列为:\n');
disp(cumsum(PCTVAR(1, :), 2));
num = input('判断并输入主成分个数: ');
disp(' ');

[XL,YL,XS,YS,beta,PCTVAR] = plsregress(X, Y, num);

%PCTVAR为主成分贡献率，第一行为X的贡献率，第二行为Y的，但以X的为准

fprintf('XL参数为标准化后X(因变量)与主成分变量U(自变量)间的系数为(参数按行顺序排列下同):\n');
disp(XL);
fprintf('YL参数为标准化后Y(因变量)与主成分变量V(自变量)间的系数为:\n');
disp(YL);
fprintf('beta参数为标准化后Y(因变量)与X(自变量)间的系数为:\n');
disp(beta);

%beta为标准化后的回归系数，下面将其还原

%求原始数据回归方程常数项
Beta(1,:) = mu(n+1:end) - mu(1:n)./sig(1:n)*beta(2:end,:).*sig(n+1:end);
%求原始数据x1,x2...xn的系数，每一列是一个回归方程
Beta(2:n+1,:) = (1./sig(1:n))'*sig(n+1:end).*beta(2:end,:);
disp('系数按列排列，依次为常数项与x1-xn:');
disp(' ');
disp(Beta);

