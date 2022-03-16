clear
clc

%变量：人均专著 师生比 科研经费 逾期毕业率

data =[
    0.1 5 5000 4.7;
    0.2 6 6000 5.6;
    0.4 7 7000 6.7;
    0.9 10 10000 2.3;
    1.2 2 400 1.8
    ];

[n, m] = size(data);

weight = [0.2 0.3 0.4 0.1]; %指标权重，题目所给或其他方法得出

%step1 指标正向化 max-x
max_v = max(data(:, 4));

data(:, 4) = max_v - data(:, 4);

%step2 数据标准化
data = data./repmat(sum(data.^2).^0.5, n, 1)

data = data.*repmat(weight, n, 1); %得到加权标准化矩阵

%求每个指标下最大值与最小值
max_line = max(data)
min_line = min(data)

%step3 求每个指标下对象相对正与负理想解的距离
dis_p = sum( (repmat(max_line, n, 1) - data ).^2 , 2).^0.5

dis_n = sum( (repmat(min_line, n, 1) - data ).^2 , 2).^0.5

%step4 求出未归一化得分
scores = dis_n./(dis_p+dis_n);
scores_std = scores./sum(scores)








