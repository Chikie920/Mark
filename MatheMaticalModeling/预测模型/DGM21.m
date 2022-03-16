clear
clc

data = [
    2.874 3.278 3.39 3.679 3.77 3.8
    ];

n = size(data, 2);

%step1 极比检验
theta = minmax([exp(-2/(n+1)) exp(2/(n+1))]); %可容覆盖范围
disp('可容覆盖范围');
disp(theta);
disp('极比范围');
disp(minmax(data(1:end-1)./data(2:end)));


%step2 得到累加序列与累减序列
data_cs = cumsum(data);
data_diff = diff(data);

%step3 求模型系数
B = [
    -1*data(1, 2:n)' ones(n-1, 1)
    ];

Y = [
    data_diff
    ]';

u = ((B'*B)^-1)*B'*Y;
a = u(1);
b = u(2);

%step4 构造预测函数
f = @(t) (b/a^2-data(1)/a)*exp(-a*(t-1))+b/a*(t-1)+(1+a)/a*data(1)-b/a^2;
%注 这里的t是相对于开始时间

%step5 预测
res = f(1:n); %预测结果(累加后)
disp('预测值');
res_re = [res(1) diff(res)] %结果还原
disp('残差');
eps = data - res_re %残差计算
disp('相对残差');
delta = abs(eps./data) %相对误差(相对残差)
disp('极比偏差');
rho = 1-((1-0.5*a)/(1+0.5*a))*(data(1:end-1)./data(2:end)) %极比偏差
