# Basic Syntax

> JS基本要点总结


JS作用域
========

JS是通过函数管理作用域的，在函数内部声明的变量只在这个函数内部可用（局部变量），同时在任何函数外部声明的或是未声明就直接使用的都是全局变量。每个JS环境都有一个环境对象（window），全局变量是该全局对象的属性之一，在任意函数外部使用`this.x`都可以访问到；
```javascript
var x = 1;
y = 0;
alert(this.x); // 1
alert(window.y); // 0
```

全局变量有个很大的问题就是在同一JS环境中，所有的JS代码都共享了该变量，肯定的会对该变量造成使用上的影响，所以应尽量避免使用全局变量。同时由于JS可以不用声明就使用某一变量，该变量会自动的变成全局变量，所以应始终使用var声明变量，为了避免忘记使用var的情况，使用strict模式`use strict`。


函数以及对象
============

对象
----

JS使用`{...}`表示一个对象，键值对以`name: tom`的形式声明，用`,`隔开，可以通过`in`判断一个对象的属性是否存在；

**this:** 如果在JS函数内部调用了this，在不同的上下文中（context），this所指向的对象都会有所不同。


命名函数
--------

```javascript
function abs(x){
	...
}

var abs = function (x){
	...	
};
```
多参数：JS天然支持多参数，`arguments`关键字以及`rest`关键字(ES6)，如下：
```javascript
function abs(){
	if(var i = 0; i < arguments.length; i++){
		alert(arguments[i]);
	}
}

function abs(a, b, ...rest){
	alert(rest);	
}

abs(1, 2, 4, 5, 6); // rest = [4, 5, 6]
```


匿名函数
--------




JS自定义事件
============
