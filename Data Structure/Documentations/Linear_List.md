# Linear_List

在非空线性表中，每个元素都有一个确定的位置，其有且仅有一个直接前驱和直接后继;
```
ADT List{
	数据对象：D = { ai | ai  ϵ ElemSet, i = 1, 2, …, n, n ≥ 0}
	数据关系：Rl = { <ai - 1, ai> | ai - 1, ai  ϵ D, i = 1, 2, …, n, n ≥ 0 }
	基本操作：
		InitList( &L );
			Re: 构造一个空的线性表L;
		DestroyList( &L );
			Init: 线性表L已存在;
			Re: 销毁线性表L；
		ListEmpty( L );
			Init：线性表L已存在;
			Re：若L为空则返回true，否则返回false;
		ClearList( L );
			Init：线性表L已存在;
			Re：将L重置为空表;
		ListLength( L );
			Init：线性表L已存在;
			Re：返回L中的数据元素个数;
		GetElem( L, i, &e );
			Init：线性表L已存在，1 ≤ i ≤ ListLength(L);
			Re：使用e返回L中第i个元素的值;
		LocalePos( L, e, compare() );
			Init：线性表L已存在，compare()是数据元素判定函数;
			Re：返回L中第1个与e满足关系compare()的数据元素的位序，若这样的数据元素不存在，则返回值为0;
		PriorElem( L, cur_e, &pre_e );
			Init：线性表L已存在;
			Re：若cur_e是L的数据元素，且不是第1个，则用pre_e返回它的前驱，否则操作失败，pre_e无定义;
		NextElem( L, cur_e, &next_e );
			Init：线性表L已存在;
			Re：若cur_e是L的数据元素，且不是最后1个，则用next_e返回它的后继，否则操作失败，next_e无定义;
		LisrInsert( &L, i, e );
			Init：线性表L已存在，且 1 ≤ i ≤ ListLength(L) + 1;
			Re：在L中第i个位置插入新的数据元素e，L的长度+1;
		ListRemove( &L, i, &e );
			Init：线性表L已存在且非空，且 1 ≤ i ≤ ListLength(L);
			Re：删除L的第i个元素，并用e返回其值，L的长度-1;
		ListTraverse( L, vist() );
			Init：线性表L已存在;
			Re：依次对L的每个元素调用函数vist();一旦vist()失败，则操作失败;
} ADT List;
```

#### sequential mapping

线性表的顺序存储结构(顺序映像)，表中相邻的元素以相邻的存储位置存放，只要确定线性表的起始位置，其任意数据元素都是可随机访问的，线性表的顺序存储结构是一种随机存取存储结构;