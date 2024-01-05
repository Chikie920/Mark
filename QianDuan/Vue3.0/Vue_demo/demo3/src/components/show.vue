<template>
    <p> {{'非响应式数据' + number_static }}</p>
    <button @click="number_static_add">+1</button>
    <p> {{'响应式数据' + number_active }}</p>
    <button @click="number_active_add">+1</button>
    <hr/>
    <p>ref创建对象型响应式数据</p>
    <p v-for="item in person_ref">{{ item }}</p>
    <button @click="person_ref_change">change</button>
    <p>reactive创建对象型响应式数据</p>
    <p v-for="item in person_reactive">{{ item }}</p>
    <button @click="person_reactive_change">change</button>
</template>

<script setup>
  import { ref, reactive } from 'vue'
  // 基本数据类型
  let number_static = 0; // 非响应式数据
  let number_active = ref(0) // 响应式数据

  //对象类型
  let person_ref = ref({name: 'chikie', age: 21}) // ref创建对象型响应式数据
  let person_reactive = reactive({name: 'john', age: 18}) // reactive创建对象型响应式数据

  function number_static_add() {
    number_static+=1
    console.log('number_static: '+number_static)
  }

  function number_active_add() {
    number_active.value+=1
    console.log(number_active)
    console.log('number_active: '+number_active.value)
  }

  function person_ref_change() {
    console.log(person_ref)
    person_ref.value.age+=1
  }

  function person_reactive_change() {
    console.log(person_reactive)
    person_reactive.age+=1
  }


</script>

<style scoped>
</style>
