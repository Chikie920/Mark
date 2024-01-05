<template>
    <form>
        <!-- <input v-bind:value="number1"> v-bind 元素动态属性绑定 -->
        <br/>
        <!-- <input :value="number2"> 元素动态属性绑定 v-bind简写 -->
        <!-- <br/>
        <button>add</button>
        <br/>
        <p>{{'Answer: '+number1 +'+'+number2+'='+res }}</p> -->
    </form>
    <!-- 仅为单项数据绑定 -->
    <form>
        <input v-model="number1"> <!-- v-bind 元素动态属性绑定 -->
        <br/>
        <input v-model="number2"> <!-- 元素动态属性绑定 v-bind简写 -->
        <br/>
        <button @click.prevent="add">add</button>
        <br/>
        <p>{{'Answer: '+number1 +'+'+number2+'='+res }}</p>
    </form>
    <button @click="changeRes">Change res</button>
    <!-- 双向数据绑定 -->
</template>


<script setup>
    import {ref, computed} from 'vue'
    let number1 = ref(0)
    let number2 = ref(0)
    let res = ref(0)

    // function add() {
    //     res.value = number1.value + number2.value
    // } // 方法实现

    /*

        仅传入get函数

    */

    // res = computed(()=>{
    //      return number1.value + number2.value
    // }) // 传入匿名函数-为get函数

    /*

        传入get与set

    */

    res = computed({
        get() {
            return number1.value + number2.value
        },
        set(val) {
            number1.value = val
            number2.value = 0
            // 这里并不能直接操纵res对象，获取res对象值是通过get()函数进行的
        }
    })

    function changeRes() {
        res.value = 9999;
        console.log(res.value)
    } // 尝试修改res控制台会警告Write operation failed: computed value is readonly，并无法修改

</script>


<style scoped>
</style>
