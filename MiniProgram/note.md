# Note

## <code>app.json</code>
全局配置文件

## <code>app.js</code>
- data参数-页面第一次渲染使用的初始数据，页面加载时，data 将会以JSON字符串的形式由逻辑层传至渲染层，因此data中的数据必须是可以转成JSON的类型：字符串，数字，布尔值，对象，数组

## <code>WXML</code>
类似于<code>HTML</code>\
WXML 通过 {{变量名}} 来绑定 WXML 文件和对应的 JavaScript 文件中的 data 对象属性\
而对于WXML元素的属性值，需要在{{}}外加双引号\
变量名区分大小写

## <code>WXSS</code>
与Web开发中的CSS类似 \
根目录中的app.wxss为项目公共样式，它会被注入到小程序的每个页面\

**WXSS文件引用方式** \
<code>@import './test_0.wxss'</code>

