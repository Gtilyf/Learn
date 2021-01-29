# spring-jpa

repository的事务自动开启？auto-commit=false的情况下：

```java
Optional<RefundTransaction> transaction = refundTransactionRepo.fetchById(refundTransactionId);
transaction.map(t -> {
  Optional<RefundProcessor> optional = refundProcessorRepo.fetchByUnique(transaction.get().getPayTransactionId());
});

// refundTransactionRepo.fetchById开启了事务，这个事务是自动开启的？给谁开启的？
JPAInterceptor.afterTransactionBegin:27 - afterTransactionBegin
JPAInterceptor.beforeTransactionCompletion:38 - beforeTransactionCompletion
JPAInterceptor.afterTransactionCompletion:33 - afterTransactionCompletion
com.ruoshui.wxpay.pay.repo.jpa.RefundTransactionRepository.findById(38.26 ms):  [statementExecuteQueryBefore-80.29 ms, statementExecuteQueryAfter-118.8 ms]
com.ruoshui.wxpay.pay.repo.jpa.RefundTransactionRepository.findById total: 237.7 ms
// refundProcessorRepo.fetchByUnique没有开启事务，因为fetchByUnique是自定义的？如果在fetchByUnique上加上@Transactional注解，同样可以开启事务，同样这个事务是给谁开启的？
JPAAspect.before:34 - aspect before
com.ruoshui.wxpay.pay.repo.jpa.RefundProcessorRepository.findByPayTransactionId(38.42 ms):  [statementExecuteQueryBefore-916.5 μs, statementExecuteQueryAfter-39.37 ms]
com.ruoshui.wxpay.pay.repo.jpa.RefundProcessorRepository.findByPayTransactionId(40.09 ms):  [statementExecuteQueryBefore-40.63 ms, statementExecuteQueryAfter-80.71 ms]
com.ruoshui.wxpay.pay.repo.jpa.RefundProcessorRepository.findByPayTransactionId total: 82.15 ms
// 事务开启，没有执行sql，也会有一定的耗时
JPAInterceptor.afterTransactionBegin:27 - afterTransactionBegin
JPAInterceptor.beforeTransactionCompletion:38 - beforeTransactionCompletion
JPAInterceptor.afterTransactionCompletion:33 - afterTransactionCompletion
com.ruoshui.wxpay.pay.repo.jpa.RefundTransactionRepository.save total: 52.19 ms non sqls
JPAInterceptor.afterTransactionBegin:27 - afterTransactionBegin
JPAInterceptor.beforeTransactionCompletion:38 - beforeTransactionCompletion
JPAInterceptor.afterTransactionCompletion:33 - afterTransactionCompletion
com.ruoshui.wxpay.pay.repo.jpa.RefundTransactionRepository.findById total: 168.2 ms non sqls
```

