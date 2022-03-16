clear
clc

data = [
    4.93 2.33 3.87 4.35 6.63 7.15 5.37 6.39 7.81 8.35
    ];

n = size(data, 2);

%step1 极比检验
theta = minmax([exp(-2/(n+1)) exp(2/(n+1))]); %可容覆盖范围
disp('可容覆盖范围');
disp(theta);
disp('极比范围');
disp(minmax(data(1:end-1)./data(2:end)));


%step2 得到累加序列
data_cs = cumsum(data);
data_z = (data_cs(1, 1:n-1)+data_cs(1, 2:n))*0.5;

%step3 求模型系数
B = [
    -data_z' (data_z.^2)'
    ];

Y = [
    data(1, 2:end)
    ]';

u = ((B'*B)^-1)*B'*Y;
a = u(1);
b = u(2);
[a, b]

%step4 构造预测函数
f = @(t) a*data(1)./(b*data(1)+(a-b*data(1))*exp(a*(t-1)));
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
