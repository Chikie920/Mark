## 模型简介

又称阻滞增长模型，常用于人口预测，图像呈S型



## 模型建立与求解

$$
设\space x(t)为第t年的人口数据,则x(0)为初始人口数据\\
设人口自然增长率为r,人口上限为x_m\\
设r为x的函数r(x)\\
则设r(x) = a+b*x\\\\
由已知得r(0) = r即初始增长率r;且r(x_m) = 0\\
可得a = r, b = -r/x_m\\
得到r(x) = r + \frac{-r*x}{x_m} = r*(1-\frac{x}{x_m})
$$

**建立Logistic模型**
$$
\begin{cases}
\frac{dx}{dt} = r*x*(1-\frac{x}{x_m})\\
x(t_0) = x_0
\end{cases}
$$


![image-20220119151307278](C:\Users\Mirai\AppData\Roaming\Typora\typora-user-images\image-20220119151307278.png)

**非线性最小二乘法求参数**

使用matlab函数`lsqnonlin()`求解参数`r`与`x_m`

