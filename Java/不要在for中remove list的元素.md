# 不要在for中remove list的元素

在for循环里remove元素

```java
List<Integer> ids = new ArrayList<>();
for (int i = 0; i < 10; i++)
  ids.add(i);

int n = 3;
// 当n = 8(倒数第二个元素)的时候，不会抛出异常，但是会得不到预期的结果
for (int i : ids) {
  ids.remove(i);
}
// 当n = 8(倒数第二个元素)的时候，会抛出异常，也会得不到预期的结果
ids.forEach(i -> {
  if (i == n)
      ids.remove(i)
  // ...do any thing for i
    System.out.print(i + " ");
});
```

运行时就有可能会抛出`ConcurrentModificationException`，如果没有抛出异常也会导致得不到预期结果。

以List.forEach举例，从ArrayList.java源码中我们可以很清楚的看到在for循环中调用remove为什么会抛出`ConcurrentModificationException`，注意modCount这个变量：

```java
/**
 * The number of times this list has been <i>structurally modified</i>.
 * Structural modifications are those that change the size of the
 * list, or otherwise perturb it in such a fashion that iterations in
 * progress may yield incorrect results.
 * 
 * If the value of this field changes unexpectedly, the iterator (or list
 * iterator) will throw a {@code ConcurrentModificationException} in
 * response to the {@code next}, {@code remove}, {@code previous},
 * {@code set} or {@code add} operations.  This provides
 * <i>fail-fast</i> behavior, rather than non-deterministic behavior in
 * the face of concurrent modification during iteration.
 */
protected transient int modCount = 0;

public boolean remove(Object o) {
  if (o == null) {
    for (int index = 0; index < size; index++)
      if (elementData[index] == null) {
        fastRemove(index);
        return true;
      }
  } else {
    for (int index = 0; index < size; index++)
      if (o.equals(elementData[index])) {
        fastRemove(index);
        return true;
      }
  }
  return false;
}

private void fastRemove(int index) {
  modCount++;
  int numMoved = size - index - 1;
  if (numMoved > 0)
    System.arraycopy(elementData, index+1, elementData, index,
                     numMoved);
  elementData[--size] = null; // clear to let GC do its work
}

...

@Override
public void forEach(Consumer<? super E> action) {
  Objects.requireNonNull(action);
  final int expectedModCount = modCount;
  @SuppressWarnings("unchecked")
  final E[] elementData = (E[]) this.elementData;
  final int size = this.size;
  for (int i=0; modCount == expectedModCount && i < size; i++) {
    // 这里如果是一些Structural modifications的话，那么就会更改modCount
    action.accept(elementData[i]);
  }
  if (modCount != expectedModCount) {
    throw new ConcurrentModificationException();
  }
}
```

当使用for-each loop时，Structural modifactions操作的是倒数第二个元素的时候，不会抛出Exception，但是会得不到预期的结果，原因就在于java的for-each loop实现方式，参考[The enhanced for statement](https://docs.oracle.com/javase/specs/jls/se8/html/jls-14.html#jls-14.14.2)：

```java
for (int i : ids)
  System.out.print(i);
// will be translated to
for (Iterator<Integer> it = ids.iterator(); it.hasNext();)
  System.out.print(i);

// tips: 数组的for-each loop实现方式
int[] idArray = new int[];
for (int i : idArray)
  System.out.print(i);
// will be translated to
for (int i = 0; i < idArray.length; i++)
  System.out.print(idArray[i]);
```

结合Iterator的实现：

```java
int cursor;       // index of next element to return
int lastRet = -1; // index of last element returned; -1 if no such

public boolean hasNext() {
  // The size of the ArrayList (the number of elements it contains).
  return cursor != size;
}

public E next() {
  checkForComodification();
  int i = cursor;
  if (i >= size)
    throw new NoSuchElementException();
  Object[] elementData = ArrayList.this.elementData;
  if (i >= elementData.length)
    throw new ConcurrentModificationException();
  cursor = i + 1;
  return (E) elementData[lastRet = i];
}

final void checkForComodification() {
  if (modCount != expectedModCount)
    throw new ConcurrentModificationException();
}
```

调用remove后，size被-1，那么再进行hasNext判断的时候，cursor == size了，那么循环就不会再进行下去，不会抛异常，但是最后一个元素就不会被遍历到了。

**正确的remove：**

```java
Iterator it = ids.iterator();
while (it.hasNext()) {
  if ((Integer) it.next() == 2)
    it.remove();
}
```

结合iterator的实现方式：

```java
public void remove() {
  if (lastRet < 0)
    throw new IllegalStateException();
  checkForComodification();

  try {
    ArrayList.this.remove(lastRet);
    // 重置cursor，那么就不会出现cursor == size的情况
    cursor = lastRet;
    lastRet = -1;
    expectedModCount = modCount;
  } catch (IndexOutOfBoundsException ex) {
    throw new ConcurrentModificationException();
  }
}
```
