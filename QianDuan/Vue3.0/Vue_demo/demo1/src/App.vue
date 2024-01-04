<template>
  <HelloWorldSetup />
  <HelloWorldGlobal />
  <HelloWorldLocal />
</template>

<!-- setup语法糖方式 -->
<!-- <script setup>
  import HelloWorldSetup from './components/HelloWorldSetup.vue'
</script> -->

<!-- 显示注册方式 -->
<script>
  import HelloWorldLocal from './components/HelloWorldLocal.vue'
  export default {
    components: {
      HelloWorldLocal
    }
  }
</script>


<style scoped>
</style>
