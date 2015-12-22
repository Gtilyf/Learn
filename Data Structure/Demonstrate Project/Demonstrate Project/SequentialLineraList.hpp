/*
	线性表的顺序实现，内存控制采用allocator实现
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
	}

	template<typename T>
	SqList<T> operator+(SqList<T> sl1, SqList<T> sl2)
	{
		using std::move;
		return SqList<T>::Merge(move(sl1), move(sl2));
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

		typedef int SIZE_TYPE;

	public:
		SqList()
			: _length(0)
			, _capacity(LIST_INIT_SIZE)
			, _isOrdered(false)
		{
			std::allocator<T> alloc;
			_base = alloc.allocate(LIST_INIT_SIZE);
		}

		/// <summary>
		///	初始化n个相同的元素，对元素进行拷贝
		/// </summary>
		SqList(const T& data, SIZE_TYPE n, bool order = false)
			: _capacity(_Rise_size(n))
			, _isOrdered(order)
		{
			std::allocator<T> alloc;

			if (n <= 0)
			{
				SqList();
				return;
			}

			_base = alloc.allocate(_capacity);

			std::uninitialized_fill_n(_base, n, data);
			_length = n;
		}

		/// <summary>
		///	初始化只有一个成员的list，用于移动元素
		/// </summary>
		SqList(const T& data, bool order = false)
			: _length(1)
			, _capacity(LIST_INIT_SIZE)
			, _isOrdered(order)
		{
			std::allocator<T> alloc;

			_base = alloc.allocate(LIST_INIT_SIZE);
			alloc.construct(_base, data);
		}

		/// <summary>
		///	释放所有的内存空间
		/// </summary>
		~SqList()
		{
			std::allocator<T> alloc;
			alloc.deallocate(_base, _capacity);
			_base = nullptr;
			_capacity = 0;
			_length = 0;
		}

		/// <summary>
		///	拷贝构造
		/// </summary>
		SqList(const SqList& sl)
			: _length(sl._length)
			, _capacity(sl._capacity)
			, _isOrdered(sl._isOrdered)
		{
			std::allocator<T> alloc;
			_base = alloc.allocate(_capacity);
			std::_Wrap_alloc<std::allocator<T>> _alloc(alloc);
			std::_Uninitialized_copy(sl._base, sl._base + _length, _base, _alloc);
		}

		/// <summary>
		///	移动构造
		/// </summary>
		SqList(SqList&& sl) _NOEXCEPT
			: _length(std::move(sl._length))
			, _base(std::move(sl._base))
			, _capacity(std::move(sl._capacity))
			, _isOrdered(sl._isOrdered)
		{
			sl._base = nullptr;
		}

		/// <summary>
		/// 列表初始化
		/// </summary>
		SqList(std::initializer_list<T> paras)
			: length(paras.size())
			, _capacity(_RiseSize(paras.size()))
			, _isOrdered(false)
		{
			std::allocator<T> alloc;
			_base = alloc.allocate(_capacity);
			std::_Wrap_alloc<std::allocator<T>> _alloc(alloc);

			std::_Uninitialized_copy(paras.begin(), paras.end(), _base, _alloc);
		}

		/// <summary>
		/// copy and move assignment operator
		/// </summary>
		SqList& operator=(SqList sl)
		{
			swap(*this, sl);
			return *this;
		}

		bool Empty()
		{
			return 0 == _length;
		}

		SIZE_TYPE Size()
		{
			return _length;
		}

		/// <summary>
		///	清空list，内存空间保留
		/// </summary>
		bool Clear()
		{
			std::allocator<T> alloc;

			T* p = _base;
			while (_length-- > 0)
				alloc.destroy(p++);
		}

		/// <summary>
		///	删除元素，返回该元素的备份
		/// </summary>
		T Remove(const SIZE_TYPE i)
		{
			if (i >= _length)
				return nullptr;

			T* p = &(*this[i]);
			T rtval = std::move(*p);
			p = nullptr;

			_Move_forward(i);
			return rtval;
		}

		/// <summary>
		///	获得某一元素的位置信息, 使用==关系运算符
		/// </summary>
		SIZE_TYPE LocalElem(const T& data)
		{
			return _Check_elem(data);
		}

		/// <summary>
		///	返回元素的前驱，如果是首元素，则返回尾元素
		/// </summary>
		T& PriorElem(const T& data)
		{
			int local = LocalElem(data);

			if (local == -1)
				return nullptr
			else if (local > 0)
				return *this[local - 1];
			else
				return *this[_length - 1];
		}

		/// <summary>
		///	返回元素的后继，如果是尾元素，则返回首元素
		/// </summary>
		T& NextElem(const T& data)
		{
			int local = LocalElem(data);

			if (local == -1)
				return nullptr;
			else if (local < _length - 1)
				return *this[local + 1];
			else
				return *this[0];
		}

		/// <summary>
		///	copy插入元素
		/// </summary>
		bool Insert(const SIZE_TYPE i, const T& data)
		{
			_Reserve(1);
			_Move_back(i);
			*(_base + i) = data;
			_length++;
			return true;
		}

		/// <summary>
		/// move插入元素
		/// </summary>
		bool Insert(const SIZE_TYPE i, T&& data)
		{
			_Reserve(1);
			_Move_back(i);
			*(_base + i) = std::move(data);
			_length++;
			return true;
		}

		/// <summary>
		///	在list尾部插入(copy)
		/// </summary>
		bool BackInsert(const T& data)
		{
			return Insert(_length, data);
		}

		/// <summary>
		///	在list尾部插入(move)
		/// </summary>
		bool BackInsert(T&& data)
		{
			return Insert(_length, std::move(data));
		}

		/// <summary>
		///	在list头部插入(copy)
		/// </summary>
		bool FrontInsert(const T& data)
		{
			return Insert(0, data);
		}

		/// <summary>
		/// 在list头部插入(move)
		/// </summary>
		bool FrontInsert(T&& data)
		{
			return Insert(0, std::move(data));
		}

		/// <summray>
		///	对list进行遍历，对所有的元素执行指定操作
		/// </summary>
		/// <param name="visitor">对元素指定的操作</param>
		/// <returns>操作成功与否</returns>
		bool Traverse(bool (*Pred) (T&))
		{
			for (int i = 0; i < Size(); i++)
			{
				if (!Pred(_base + i))
					return false;
			}
			return true;
		}

		/// <summary>
		///	元素访问，返回该元素的引用
		/// </summary>
		T& GetElem(SIZE_TYPE i)
		{
			return *this[i];
		}

		T& operator[](SIZE_TYPE i)
		{
			if (Empty() || !_Is_legel(i))
				return nullptr;

			T* p = _base;

			return *(p + i);
		}
		const T& operator[](SIZE_TYPE i) const
		{
			if (Empty() || !_Is_legel(i))
				return nullptr;

			const T* p = _base;

			return *(p + i);
		}

		/// <summary>
		///	list union，将另一个SqList并入当前SqList;
		/// 被插入的元素应当和原来的list没有关联，移动或者拷贝
		/// </summary>
		SqList& Union(SqList sl)
		{
			T* first = sl._base;
			T* last = sl._base + sl.Size();
			while (first++ != last){
				BackInsert(std::move(*first));
			}
			return *this;
		}
		SqList& operator+=(SqList sl)
		{
			return Union(std::move(sl));
		}

		/// <summary>
		///	list Merge, 返回新的SqList，两个SqList的元素并入新的SqList
		/// 被插入的元素应当和原来的list没有关联，移动或者拷贝
		/// </summary>
		static SqList Merge(SqList sl1, SqList sl2)
		{
			sl1 += std::move(sl2);
			return sl1;
		}
		friend SqList operator+ <> (SqList sl1, SqList sl2);

		friend bool operator== <> (const SqList& sl1, const SqList& sl2);
		friend bool operator!= <> (const SqList& sl1, const SqList& sl2);
		friend bool operator> <> (const SqList& sl1, const SqList& sl2);
		friend bool operator< <> (const SqList&, const SqList&);
		friend void swap <>(SqList&, SqList&);

	private:
		// list默认初始容量
		const SIZE_TYPE LIST_INIT_SIZE = 10;
		// list当前容量
		int _capacity;
		// list元素基址
		T* _base;
		// 元素长度
		int _length;
		// list是否有序
		bool _isOrdered;

		/// <summary>
		///	检查元素是否存在
		/// </summary>
		SIZE_TYPE _Check_elem(const T& elem) const _NOEXCEPT
		{
			SIZE_TYPE index = 0;
			while (index++ < _length)
			{
				if (*(_base + index) == elem)
					return index;
			}
			return -1;
		}

		/// <summary>
		///	检测下标是否合法
		/// </summary>
		bool _Is_legel(SIZE_TYPE i)
		{
			return i > 0 && i < Size();
		}

		/// <summary>
		///	返回未使用的容量大小
		/// </summary>
		SIZE_TYPE _Unused_capacity() const _NOEXCEPT
		{
			return _capacity - _length;
		}

		/// <summary>
		///	容量增长
		/// </summary>
		/// @count: 新容量
		void _Reallocate(SIZE_TYPE count)
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

		/// <summary>
		///	确定是否有足够的空间
		/// </summary>
		/// @count: 需要的容量
		void _Reserve(SIZE_TYPE count)
		{
			if (count < _Unused_capacity())
				return;
			else if (count > _Unused_capacity()){
				SIZE_TYPE newSize = _Rise_size(_capacity);
				if (count > newSize - _length)
					newSize = _capacity + count;
				_Reallocate(newSize);
			}
		}

		/// <summary>
		///	定义容量增长的方式
		/// </summary>
		SIZE_TYPE _Rise_size(SIZE_TYPE count) const _NOEXCEPT
		{
			return count + count / 2;
		}

		/// <summary>
		/// 将第i位置之后的元素依次向后移动
		/// </summary>
		void _Move_back(SIZE_TYPE i)
		{
			T* last = _base + Size();
			T* dest = _base + i;

			std::allocator<T> alloc;
			alloc.construct(last);

			for (; last != dest; last--)
				*last = std::move(*(last - 1));

			_length++;
		}

		/// <summary>
		///	将第i位置之后的元素依次向前移动
		/// </summary>
		void _Move_forward(SIZE_TYPE i)
		{
			T* dest = _base + i;
			T* last = _base + Size() - 1;
			for (; dest != last; dest++)
				*dest = std::move(*(dest + 1));

			std::allocator<T> alloc;
			alloc.deallocate(last);

			_length--;
		}
	};

}