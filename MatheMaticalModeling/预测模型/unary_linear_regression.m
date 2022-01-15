clear;clc;
x = [2.9 1.8 2.4 3.0 3.5 3.9 4.4 4.8 5.0]';
y = [7.5 3.57 3.0 5.3 8.9 11.69 13.1 13.6 15.3]';
%需要列向量
X = [ones(size(x, 1), 1) x]; % 根据文档可知，需要增加一列数值为1的值，用于求截距
b = regress(y, X);
disp("回归系数为(b0 - bk):");
disp(b);

func = @(x) b(1) + b(2)*x;
SSE = sum(sum((y - func(x(:))).^2));
SSR = sum((func(x(:)) - mean(y)).^2);
SST = SSE+SSR;
R_double = SSR/SST;

disp("误差平方和SSE: "+SSE);
disp("回归平方和SSR: "+SSR);
disp("总偏差平方和SST: "+SST);
disp("拟合优度(判定系数): "+R_double);

[h1, p1] = vartest2(x, y);
[h2, p2] = ttest2(x, y); %这里只检验了x

disp("F检验: "+h1+" "+p1);
disp("t检验: "+h2+" "+p2);

%%%%%%%
fprintf("\n\n\n");
stats = regstats(y, x);
disp("------方差分析表------");
fprintf("误差平方和SSE: %f  自由度: %f\n", stats.fstat.sse, stats.fstat.dfe);
fprintf("回归平方和SSR: %f  自由度: %f\n", stats.fstat.ssr, stats.fstat.dfr);
fprintf("总偏差平方和SST: %f  自由度: %f\n", stats.fstat.ssr+stats.fstat.sse, stats.fstat.dfr+stats.fstat.dfe);
fprintf("R^2: %f\n", stats.rsquare);
fprintf("F值: %f  P值: %f\n", stats.fstat.f, stats.fstat.pval);
disp("------回归系数检验表------");
fprintf("b0估计值: %f  t值: %f  p值: %f\n", stats.beta(1), stats.tstat.t(1), stats.tstat.pval(1));
fprintf("b1估计值: %f  t值: %f  p值: %f\n", stats.beta(2), stats.tstat.t(2), stats.tstat.pval(2));