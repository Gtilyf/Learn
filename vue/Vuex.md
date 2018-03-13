# Vuex

用于解决**多个组件共享状态**时遇到的一系列问题，把组件的共享状态抽离出来，以一个全局单例模式管理。每个Vuex应用的核心是store，通过组件的store选项注册，并且该组件的所有子组件，都能共享该store。

1. 不能直接改变store中的状态，只能通过**提交(commit) mutation**的方式进行修改；
2. Vuex的状态存储是响应式的；

![](./img/vuex.png)

```shell
├── index.html
├── main.js
├── api
│   └── ... # 抽取出API请求
├── components
│   ├── App.vue
│   └── ...
└── store
    ├── index.js          # 我们组装模块并导出 store 的地方
    ├── actions.js        # 根级别的 action
    ├── mutations.js      # 根级别的 mutation
    └── modules
        ├── cart.js       # 购物车模块
        └── products.js   # 产品模块
```

