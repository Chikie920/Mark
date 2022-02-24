clear
clc

Mdl = arima('AR',{0.75,0.15},'SAR',{0.9,-0.5,0.5},...
    'SARLags',[12,24,36],'MA',-0.5,'Constant',2,...
    'Variance',1);
rng(1);
y = simulate(Mdl,1000); 
%模拟数据


figure(1)
autocorr(y, 'NumLags', 40); %绘制时间序列数据的自相关系数图像
figure(2)
parcorr(y); %绘制时间序列数据的偏自相关系数图像

%白噪声检验

Lags=(1:40);   %滞后项数
[H,pValue,Qstat,CriticalValue]=lbqtest(y,'lags',Lags);
%H,结果，p概率，Qlb的统计量,临界值
fprintf('%15s%15s%15s%15s','是否拒绝原假设(1-非白噪声序列)', '延迟阶数','卡方统计量','p值');%把逗号后的字符串，15s的空格
fprintf('\n');
for i=1:length(Lags)    %i=1,时候为6，i=2时候为12
    fprintf('%15d%30d%22f%19f',H(i),Lags(i),Qstat(i),pValue(i));
    fprintf('\n');
end


