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



vue2中`data`函数内的数据默认为响应式，而vue3的`setup`函数中的数据则不是(数据可以改变但是页面显示不会改变)



### ref函数

`ref`函数既可以创建响应式的基本数据，又可以创建响应式对象

**使用方式**

```vue
<script>
    import { ref } from 'vue' // 必须引入

    let number = ref(0) // 创建了一个响应式的数值型数据，初始值为0

    /*
    实际上就是讲number封装在一个Ref对象中
    */
    
    number.value += 1 // 要想操作数据必须加上value，而template中无需加.value
    
    let person_ref = ref({name: 'chikie', age: 21}) // ref创建对象型响应式数据
    
    person_ref.value.age+=1 // 操作ref响应式对象数据
    
</script>
```

注意操作ref响应式数据时必须加**`.value`**，实际上ref创建对象型响应式数据底层还是由reactive实现的



### reactive函数

`reactive`函数仅支持创建响应式对象

**使用方式**

```vue
<script>
    import { reactive } from 'vue' // 必须引入
    
    let person_ref = reactive({name: 'chikie', age: 21}) // reactive创建对象型响应式数据
    
    person_ref.age+=1 // 操作reactive响应式对象数据
    
</script>
```



**见demo3**



### ref与reactive创建响应式对象替换

- `reactive`所创建响应式对象重新赋值一个新对象，会**失去**响应式（可以使用`Object.assign`去整体替换）

```vue
<script>
let person = reactive({name:'chikie', age:19})

person = {name:'john', age:21}// 页面不更新
person = reactive({name:'john', age:21} )// 页面不更新
Object.assign(perosn, {name:'john', age:21})// 正确做法
</script>
```

- 而`ref`所创建响应式对象可以直接重新赋值一个新对象 

```vue
<script>
let person = ref({name:'chikie', age:19})

person.value = {name:'john', age:21} // 只要动了value必为响应式
</script>
```



## template元素属性绑定

`v-bind`将元素属性如class、id、value等与变量绑定，方式`v-bind:class`....

但仅为单项绑定

双向绑定使用`v-model`

**示例见demo4**



## 计算属性与方法

计算属性对同一数据有缓存，多个同一数据只用计算一次，而方法则需计算多次

计算属性借助`computed()`函数

- computed函数返回数据为`ref`型对象
- computed函数只传入一个参数时，该参数为get函数，此时返回数据只读
- computed函数也可以接受一个带有 `get` 和 `set` 函数的**对象**来创建一个可写的 `ref` 对象

**示例见demo5**



## 事件监听
