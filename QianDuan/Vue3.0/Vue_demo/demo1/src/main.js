import { createApp } from 'vue'
import App from './App.vue'

import HelloWorldGlobal from './components/HelloWorldGlobal.vue'

/*
原始代码
createApp(App).mount('#app')
*/

const app = createApp(App)

app.component('HelloWorldGlobal', HelloWorldGlobal)
// 全局注册组件

// 注册组件必须在挂载之前
app.mount('#app')
