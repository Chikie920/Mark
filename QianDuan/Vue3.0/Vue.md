# **Vue启动！**



## **创建vue项目**

```shell
npm create vue@latest //创建项目
// 输入项目名称，直接回车，创建完成后进入工作目录
npm install //安装依赖
npm run dev //运行
```



## **组件导入**



### 导入-注册方式

#### 全局注册

在main.js内注册

注册后全局都可以使用该模板，不建议使用会导致模板依赖关系不明确



#### 局部注册

当前组件内注册

仅在当前组件可使用，其他组件甚至是子组件内都无法使用



**显示注册方式**

```vue
<script>
  import template_name from './components/template_name.vue'
  export default {
    components: {
      template_name
    }
  }
</script>
```



##### setup方式

```vue
<script setup>
    import template_name from './components/template_name.vue'
</script>
```

此种方法无需注册组件（隐式注册），导入后可直接使用



**示例见demo1**



## style-scope属性

加上该属性，其CSS样式 只会影响当前组件的元素



## 模板语法



### vue2方式-选项式

数据与函数必须分开写

```vue
<template>
    <h1>Message: {{ msg }}</h1>
    <p>数组</p>
    <p v-for="(item, index) in array" :key="index">{{ item }}</p>
    <p>对象</p>
    <p v-for="(value, key) in data">{{ key +': '+ value }}</p>
    <button @click="clickButton">Click</button>
</template>

<script>
    export default {
        data() {
            return {
                msg : 'Hello World!',
                array : [1, 2, 3, 4],
                data : {name:'chikie', age:21, gender:'female'}
            }
        },

        methods: {
            clickButton() {
                alert('You Click')
            }
        }
        
    }
</script>

<style>
</style>
```



### vue3方式-组合式

数据与函数写在一起

```vue
<template>
    <h1>Message: {{ msg }}</h1>
    <p>数组</p>
    <p v-for="(item, index) in array" :key="index">{{ item }}</p>
    <p>对象</p>
    <p v-for="(value, key) in data">{{ key +': '+ value }}</p>
    <button @click="clickButton">Click</button>
</template>

<script>
    export default {
        setup() {
            let msg = 'Hello World!'
            let array = [1, 2, 3, 4]
            let data = {name:'chikie', age:21, gender:'female'}
            // 数据
            
            function clickButton() {
                alert('You Click')
            }
            // 函数

            return {msg, array, data, clickButton}
            // 必须返回才能够使用
        }
    }
</script>

<style>
</style>
```



### setup语法糖

```vue
<script>
     export default {
        setup() {
			数据
			函数
			return {数据, 函数}
		}
	}
</script>
精简为
<script setup>
    let msg = 'Hello World!'
        let array = [1, 2, 3, 4]
        let data = {name:'chikie', age:21, gender:'female'}
        
        function clickButton() {
            alert('You Click')
        }
</script>
无需写setup函数与返回对象
```



**见demo2**





## 响应式数据



vue2中`data`函数内的数据默认为响应式，而vue3的`setup`函数中则不是(为死数据)
