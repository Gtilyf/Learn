# Result

#### Why

1. 返回数据

2. 错误信息由具体业务逻辑决定的，返回的时候能否带上错误信息？

3. 能否将错误类型区分开，调用方可以根据不同的错误类型做相应的处理，并且方便处理（switch...case...）？（**非必须**）

4. 业务返回语义明确，真实业务对象

5. Optional的正确使用姿势？**链式操作**？一眼就可以看出逻辑关系？
   
   - 错误类型一致，返回数据类型也一致
     
     - 数据内容未修改，只是使用 ⇒ `consumer`
     
     - 数据内容有修改，需要更改 ⇒ `then & flatThen`
   
   - 错误类型不一致，返回数据类型一致（一致的情况，还区分错误类型，合理吗？） ⇒  `then`
   
   - 错误类型一致，返回数据不一致 &rArr; `apply`
   
   - 错误类型不一致，返回数据不一致 &rArr; `apply`
   
   - 获取返回数据，failed的时候，可以指定默认值 ⇒ `T orElese()`
   
   - 获取返回数据，failed的时候，抛出异常 ⇒ `orElseThrow()`
   
   - failed的时候，重试操作 ⇒ `retry`
   
   - 对错误情况的处理 ⇒ `consume` ?

6. 错误数据显性化？与正常的业务数据区分开
   
   . 错误数据如何传入链式操作的下一级
   
   . 对错误数据的处理 ⇒ `consume` ?

#### How

`AbstractResult`

`ThinResult`

    `ThinError`：只有错误信息`errMsg`

`Result`

    `Error`：错误信息和错误类型`error` & `errMsg`

`FatResult`

    `FatError`：错误信息，错误类型，错误数据`error` & `errMsg` & `errData`
