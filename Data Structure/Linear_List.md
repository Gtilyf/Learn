# Linear_List

在非空线性表中，每个元素都有一个确定的位置，其有且仅有一个直接前驱和直接后继;

#### sequential mapping

线性表的顺序存储结构（顺序映像）表中相邻的元素以相邻的存储位置存放，只要确定线性表的起始位置，其任意数据元素都是可随机访问的，线性表的顺序存储结构是一种随机存取存储结构：
- 具有连续的存储空间，支持随机访问，内存管理采用std::allocator;
- 在除尾元素之外的任何位置插入、删除元素都需要进行移动操作;
![内存结构](../img/Sequential-Linear-List.png)
- 访问操作: 随机访问，*(_first + n)
- 插入操作：
	1) 插入[ first, last )
![insert range](../img/Sequential-Linear-List-InsertRange.png)
```c++
template<class _FwdIt> inline
	void _Rotate(_FwdIt _First, _FwdIt _Mid, _FwdIt _Last,
		forward_iterator_tag)
	{	// rotate [_First, _Last), forward iterators
	for (_FwdIt _Next = _Mid; ; )
		{	// swap [_First, ...) into place
		_STD iter_swap(_First, _Next);
		if (++_First == _Mid)
			if (++_Next == _Last)
				break;	// done, quit
			else
				_Mid = _Next;	// mark end of next interval
		else if (++_Next == _Last)
			_Next = _Mid;	// wrap to last end
		}
	}
```
	2) 插入val * count
![insert count * val](../img/Sequential-Linear-List-InsertCount.png)
```c++
template<class _BidIt1,
	class _BidIt2> inline
	_BidIt2 _Move_backward(_BidIt1 _First, _BidIt1 _Last,
		_BidIt2 _Dest, _Nonscalar_ptr_iterator_tag)
	{	// move [_First, _Last) backwards to [..., _Dest), arbitrary iterators
	while (_First != _Last)
		*--_Dest = _STD move(*--_Last);
	return (_Dest);
	}
```