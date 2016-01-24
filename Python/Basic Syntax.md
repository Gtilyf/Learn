# Python basic syntax

> python基本应用，总结自[廖雪峰的python教程](http://www.liaoxuefeng.com/wiki/0014316089557264a6b348958f449949df42a6d3a2e542c000)

#### basic

python是动态语言，不需要在定义变量是申明变量类型，并且同意变量可以在不同的时候赋予不同类型的值; python以缩进来区分层级，如下：
```python
def function():
	# 进入函数体
	if True:
		# 进入if块
		print('hello word');
# 退出函数体
print('function over')
```

除了最基本的变量类型（int, float, string, bool(True, False)）等之外，在python中运用的比较多的还有list、tulp、dict、set;
```python
# list (ordered, mutable, support indexing)
keys = ['a', 'b', 'c']
classmates.append('ad')
classmates.insert(2, 'safd')
print(keys[2], len(keys))

# tuple (ordered, immutable, support indexing)
keys = ('a', 'b', 'c')

# dict (key-value)
names = {'a': 'adf', 'b': 'adsf'}
names['c'] = 'abc'
for key, value in names:
	print(key, value)

# set (unordered, unrepeatable, not support indexing)
s = set(['hello', 'world'])
```

#### python高级特性

- **slice**

取list或者tulp中的部分元素，用于取指定索引范围内等元素：
```python
keys = ['a', 'b', 'c']
# 取出keys[0]~keys[2]的元素
print(keys[0:2])
# 取倒数第一个元素
print(keys[-1])
```

- **Iteration**

遍历容器中的内容，for...in...
```python
dict = {'asdf' : 'dsfa', 'ads' : 'adfasf'}
for k, v in dict.iteritems():
	print k, v

from collections import Iterable
if isinstance(List, Iterable):
	for i, l in enumerate(List):
		print i, l
```

- **list comprehensions and generator**

列表生成式，
```python
# list comprehensions
x2 = [x * x for x in range(1, 11)]
list = [s.lower() if isinstance(s, str) else s for s in List]

# generator
g = (x * x for x in range(10))
for n in g:
	print(n)

# generator function
def fib(max):
    n, a, b = 0, 0, 1
    while n < max:
        yield b
        a, b = b, a + b
        n = n + 1
    return 'done'
for n in fib(6):
	print(n)
```
