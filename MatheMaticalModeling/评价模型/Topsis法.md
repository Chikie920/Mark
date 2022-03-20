又称优劣解距法或理想解法

这种方法通过构造评价问题的正理想解和负理想解(虚拟解)，即各指标的最优解和最劣解，通过计算每个方案到理想方案的相对贴近度，即靠近正理想解和远离负理想解的程度，来对方案进行排序，从而选出最优方案。



## 模型思路



### 统一指标类型

**负面指标正向化**

对于成本型指标，该指标中得分最大值减去该指标下所有得分，将指标统一便于后续方法的统一
$$
max - x_i
$$

### 标准化处理

去量纲

<img src="https://raw.githubusercontent.com/Chikie920/Mark/main/Sources/images_math/image-20220116192604197.png" alt="image-20220116192604197" style="zoom:80%;" />



### 权重

可以给各指标加上权重，构造带权重的topsis方法

只需用标准化后的矩阵中每列元素乘以对映列(指标下)的权重即可，而权重的计算可以依靠AHP或熵权法



### 计算得分

分别求得每项指标下最大值与最小值，分别作为虚拟的最佳与最差方案，再分别求每个方案下每个指标的值对于最佳方案的距离(欧式距离)`D_positive`，同样求得每个方案下每个指标对于最差方案的距离`D_negative`，使用公式得到未归一化的得分，再归一化即可得到每个方案最终得分。



<img src="https://raw.githubusercontent.com/Chikie920/Mark/main/Sources/images_math/image-20220116192501669.png" alt="image-20220116192501669" style="zoom:80%;" />

<img src="https://raw.githubusercontent.com/Chikie920/Mark/main/Sources/images_math/image-20220116192906036.png" alt="image-20220116192906036" style="zoom:80%;" />




$$
D^+_i与D^-_i后求得未归一化得分S_i，再归一化得分即可得到最终得分，最后进行排序即可\\
其中\space S_i = \frac{D^-_i}{D^+_i+D^-_i}
$$


### 有关指标的转化

- 极小型转极大型，正向化公式如上

- 中间型转极大型

![image-20220116193505241](https://raw.githubusercontent.com/Chikie920/Mark/main/Sources/images_math/image-20220116193505241.png)

- 区间型转极大型

![image-20220116193532411](https://raw.githubusercontent.com/Chikie920/Mark/main/Sources/images_math/image-20220116193532411.png)

