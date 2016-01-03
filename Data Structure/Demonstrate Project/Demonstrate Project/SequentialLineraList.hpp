/*
	线性表的顺序实现，内存控制采用allocator实现.

*/

#include <iostream>
#include <memory>
#include <stdexcept>

namespace DS{

	template<typename T>
	class SqList;

	template<typename T>
	void swap(SqList<T>& sl1, SqList<T>& sl2)
	{
		using std::swap;
		swap(sl1._length, sl2._length);
		swap(sl1._base, sl2._base);
		swap(sl1._capacity, sl2._capacity);
		swap(sl1._isOrdered, sl2._isOrdered);
	}

	template<typename T>
	SqList<T> operator+(SqList<T> sl1, SqList<T> sl2)
	{
		sl1 += std::move(sl2);
		return sl1;
	}

	template<typename T>
	bool operator==(const SqList<T>& sl1, const SqList<T>& sl2)
	{
		return sl1._base == sl2._base;
	}

	template<typename T>
	bool operator!=(const SqList<T>& sl1, const SqList<T>& sl2)
	{
		return !(sl1 == sl2);
	}

	template<typename T>
	bool operator>(const SqList<T>& sl1, const SqList<T>& sl2)
	{
		return sl1.Size() > sl2.Size();
	}

	template<typename T>
	bool operator<(const SqList<T>& sl1, const SqList<T>& sl2)
	{
		return !(sl1 > sl2);
	}

	template<typename T>
	class SqList{

		typedef int size_type;

	public:
		SqList()
			: _capacity(LIST_INIT_SIZE)
			, _length(0)
			, _isOrdered(false)
		{
			std::allocator<T> alloc;
			_base = alloc.allocate(LIST_INIT_SIZE);
		}

		// 初始化n个相同的元素，对元素进行拷贝
		SqList(const T& data, size_type count, bool order = false)
			: _capacity(_Rise_size(count))
			, _isOrdered(order)
		{
			std::allocator<T> alloc;

			if (count <= 0)
			{
				SqList();
				return;
			}

			_base = alloc.allocate(_capacity);

			std::uninitialized_fill_n(_base, count, data);
			_length = count;
		}

		// 初始化只有一个成员的list
		SqList(const T& data, bool order = false)
			: _capacity(LIST_INIT_SIZE)
			, _length(1)
			, _isOrdered(order)
		{
			std::allocator<T> alloc;

			_base = alloc.allocate(LIST_INIT_SIZE);
			alloc.construct(_base, data);
		}

		// 释放所有的内存空间
		~SqList()
		{
			std::allocator<T> alloc;
			alloc.deallocate(_base, _capacity);
			_base = nullptr;
			_capacity = 0;
			_length = 0;
		}

		// 拷贝构造
		SqList(const SqList& sl)
			: _capacity(sl._capacity)
			, _length(sl._length)
			, _isOrdered(sl._isOrdered)
		{
			std::allocator<T> alloc;
			_base = alloc.allocate(_capacity);
			if (sl._length == 0)
				return;
			std::_Wrap_alloc<std::allocator<T>> _alloc(alloc);
			std::_Uninitialized_copy(sl._base, sl._base + _length, _base, _alloc);
		}

		// 移动构造
		SqList(SqList&& sl) _NOEXCEPT
			: _capacity(std::move(sl._capacity))
			, _base(std::move(sl._base))
			, _length(std::move(sl._length))
			, _isOrdered(sl._isOrdered)
		{
			sl._base = nullptr;
		}

		// 列表初始化
		SqList(std::initializer_list<T> paras)
			: _length(paras.size())
			, _capacity(_Rise_size(paras.size()))
			, _isOrdered(false)
		{
			std::allocator<T> alloc;
			_base = alloc.allocate(_capacity);
			if (paras.size() == 0)
				return;
			std::_Wrap_alloc<std::allocator<T>> _alloc(alloc);
			std::_Uninitialized_copy(paras.begin(), paras.end(), _base, _alloc);
		}

		// copy and move assignment operator
		SqList& operator=(SqList sl)
		{
			swap(*this, sl);
			return *this;
		}

		bool Empty()
		{
			return 0 == _length;
		}

		size_type Size()
		{
			return _length;
		}

		// 清空list，内存空间保留
		void Clear()
		{
			std::allocator<T> alloc;

			T* p = _base;
			for (; _length > 0; _length--)
				alloc.destroy(p++);
		}

		// 删除元素，返回该元素的备份
		T Remove(const size_type index)
		{
			T* p = _base + index;
			T rtval = std::move(*p);
			p = nullptr;

			_Move_forward(index + 1);
			_length--;
			return rtval;
		}

		// 获得某一元素的位置信息, 使用==关系运算符
		size_type LocalElem(const T& data)
		{
			return _Check_elem(data);
		}

		bool Exist(const T& data)
		{
			return (LocalElem(data) > 0);
		}

		// 返回元素的前驱，如果是首元素，则返回尾元素
		T& PriorElem(const T& data)
		{
			int local = LocalElem(data);

			if (local > 0)
				return *this[local - 1];
			else
				return *this[_length - 1];
		}

		// 返回元素的后继，如果是尾元素，则返回首元素
		T& NextElem(const T& data)
		{
			int local = LocalElem(data);

			if (local < _length - 1)
				return *this[local + 1];
			else
				return *this[0];
		}

		// copy插入元素
		bool Insert(const size_type index, const T& data)
		{
			_Reserve(1);
			_Move_back(index);
			*(_base + index) = data;
			_length++;
			return true;
		}

		// move插入元素
		bool Insert(const size_type index, T&& data)
		{
			_Reserve(1);
			_Move_back(index);
			*(_base + index) = std::move(data);
			_length++;
			return true;
		}

		// 在list尾部插入(copy)
		bool BackInsert(const T& data)
		{
			return Insert(_length, data);
		}

		// 在list尾部插入(move)
		bool BackInsert(T&& data)
		{
			return Insert(_length, std::move(data));
		}

		// 在list头部插入(copy)
		bool FrontInsert(const T& data)
		{
			return Insert(0, data);
		}

		// 在list头部插入(move)
		bool FrontInsert(T&& data)
		{
			return Insert(0, std::move(data));
		}

		// 对list进行遍历，对所有的元素执行Pred操作
		bool Traverse(bool (*Pred) (T&))
		{
			for (int i = 0; i < Size(); i++)
			{
				if (!Pred(*(_base + i)))
					return false;
			}
			return true;
		}

		// 元素访问，返回该元素的引用
		T& GetElem(const size_type index)
		{
			return this->operator[index];
		}

		T& operator[](const size_type index)
		{
			return *(_base + index);
		}
		const T& operator[](const size_type index) const
		{
			return *(_base + index);
		}

		
		/*
			list union，将另一个SqList并入当前SqList;
			被插入的元素应当和原来的list没有关联，移动或者拷贝
		*/
		SqList& Union(SqList sl)
		{
			T* first = sl._base;
			T* last = sl._base + sl.Size();
			for (; first != last; first++) {
				if (!Exist(*first))
					BackInsert(std::move(*first));
			}

			return *this;
		}
		SqList& operator+=(SqList sl)
		{
			return Union(std::move(sl));
		}

		/*
			list Merge, 返回新的SqList，两个SqList的元素并入新的SqList
			被插入的元素应当和原来的list没有关联，移动或者拷贝
		*/
		static SqList Merge(SqList sl1, SqList sl2)
		{
			sl1 += std::move(sl2);
			return sl1;
		}
		friend SqList operator+ <> (SqList, SqList);

		friend bool operator== <> (const SqList&, const SqList&);
		friend bool operator!= <> (const SqList&, const SqList&);
		friend bool operator> <> (const SqList&, const SqList&);
		friend bool operator< <> (const SqList&, const SqList&);
		friend void swap <>(SqList&, SqList&);

	private:
		// list默认初始容量
		const size_type LIST_INIT_SIZE = 10;
		// list当前容量
		int _capacity;
		// list元素基址
		T* _base;
		// 元素长度
		int _length;
		// list是否有序
		bool _isOrdered;

		// 检查元素是否存在
		// TODO: 使用algorithms find查找元素
		size_type _Check_elem(const T& elem) const _NOEXCEPT
		{
			size_type index = 0;
			for (; index < _length; index++)
			{
				if (*(_base + index) == elem)
					return index;
			}
			return -1;
		}

		// 检测下标是否合法
		bool _Is_legel(const size_type index)
		{
			return index > 0 && index < Size();
		}

		// 返回未使用的容量大小>
		size_type _Unused_capacity() const _NOEXCEPT
		{
			return _capacity - _length;
		}

		// 容量增长
		void _Reallocate(const size_type count)
		{
			T* first = _base;
			T* last = _base + _length;
			std::allocator<T> alloc;
			std::_Wrap_alloc<std::allocator<T>> _alloc(alloc);
			_base = alloc.allocate(count);

			std::_Uninitialized_move(first, last, _base, _alloc);
			alloc.deallocate(first, _capacity);
			_capacity = count;
		}

		// 确定是否有足够的空间
		void _Reserve(const size_type count)
		{
			if (count < _Unused_capacity())
				return;
			else if (count > _Unused_capacity()){
				size_type newSize = _Rise_size(_capacity);
				if (count > newSize - _length)
					newSize = _capacity + count;
				_Reallocate(newSize);
			}
		}

		// 定义容量增长的方式
		size_type _Rise_size(const size_type count) const _NOEXCEPT
		{
			return count + count / 2;
		}

		// 将第i位置之后的元素依次向后移动[index, _length)
		void _Move_back(const size_type index)
		{
			if (index >= Size())
				return;

			T* last = _base + Size();
			T* dest = _base + index;

			std::allocator<T> alloc;
			alloc.construct(last);

			for (; last != dest; last--)
				*last = std::move(*(last - 1));
		}

		// 将第i位置之后的元素依次向前移动[index, _length)
		void _Move_forward(const size_type index)
		{
			if (index >= Size())
				return;

			T* dest = _base + index;
			T* last = _base + Size();
			for (; dest != last; dest++)
				*dest = std::move(*(dest));

			std::allocator<T> alloc;
			alloc.destroy(dest);
		}
	};

}