# Function

> 总结自C++ Primer，对C++函数的使用

**static object :**

_local static object_ will not be released  after the end of the function, will be released after the end of program.

**function pointer :**

```
// 定义函数指针
typedef char (*FUN) (int, char);
FUN fp = fun;
char (*fp) (int, char);

int (*f1(int)) (int *, int); // 返回int (int *, int)类型的函数指针
auto f1(int) -> int(*)(int *, int);
```

**reference and function :**

**lvalue, rvalue and function :**

函数返回引用得到左值，否则得到右值;