<template>
    <h1>Message: {{ msg }}</h1>
    <p>数组</p>
    <p v-for="(item, index) in array" :key="index">{{ item }}</p>
    <p>对象</p>
    <p v-for="(value, key) in data">{{ key +': '+ value }}</p>
    <button @click="clickButton">Click</button>
</template>

<!-- vue2风格 -->
<!-- <script>
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
</script> -->

<!-- vue3风格 -->
<!-- <script>
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
</script> -->

<!-- vue3 setup语法糖 -->
<script setup>
    let msg = 'Hello World!'
        let array = [1, 2, 3, 4]
        let data = {name:'chikie', age:21, gender:'female'}
        
        function clickButton() {
            alert('You Click')
        }
</script>

<style>
</style>