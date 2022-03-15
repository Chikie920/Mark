又称优劣解距法



## 模型思路



### 统一指标类型

**负面指标正向化**

该指标中得分最大值减去该指标下所有得分
$$
max - x_i
$$

### 标准化处理

<img src="https://github.com/Chikie920/Mark/tree/main/Sources/images_math/image-20220116192604197.png" alt="image-20220116192604197" style="zoom:80%;" />





### 计算得分

<img src="https://github.com/Chikie920/Mark/tree/main/Sources/images_math/image-20220116192501669.png" alt="image-20220116192501669" style="zoom:80%;" />

<img src="https://github.com/Chikie920/Mark/tree/main/Sources/images_math/image-20220116192906036.png" alt="image-20220116192906036" style="zoom:80%;" />




$$
D^+_i与D^-_i后求得未归一化得分S_i，再归一化得分即可得到最终得分，最后进行排序即可\\
其中\space S_i = \frac{D^-_i}{D^+_i+D^-_i}
$$


### 有关指标的转化

- 极小型转极大型，正向化公式如上

- 中间型转极大型

![image-20220116193505241](https://github.com/Chikie920/Mark/tree/main/Sources/images_math/image-20220116193505241.png)

- 区间型转极大型

![image-20220116193532411](https://github.com/Chikie920/Mark/tree/main/Sources/images_math/image-20220116193532411.png)

