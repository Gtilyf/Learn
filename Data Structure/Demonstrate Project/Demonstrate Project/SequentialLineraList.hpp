/*
	线性表的顺序实现，内存控制采用allocator实现.

*/

#include <iostream>
#include <memory>
#include <stdexcept>
#include <iostream>

namespace DS{

	template<typename T>
	class SqList;

	template<typename T>
	void swap(SqList<T>& sl1, SqList<T>& sl2)
	{
		using std::swap;
		swap(sl1._first, sl2._first);
		swap(sl1._last, sl2._last);
		swap(sl1._end, sl2._end);
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
		return sl1._first == sl2._first;
	}

	template<typename T>
	bool operator!=(const SqList<T>& sl1, const SqList<T>& sl2)
	{
		return !(sl1 == sl2);
	}

	template<typename T>
	bool operator>(const SqList<T>& sl1, const SqList<T>& sl2)
	{
		return sl1.size() > sl2.size();
	}

	template<typename T>
	bool operator<(const SqList<T>& sl1, const SqList<T>& sl2)
	{
		return !(sl1 > sl2);
	}

	template<typename T>
	class SqList {

		typedef std::size_t size_type;
		typedef T* pointer;
		typedef T& reference;

	public:
		SqList()
		{
			_Create_Mem(LIST_INIT_SIZE);
			_last = _first;
		}

		// 初始化n个相同的元素，对元素进行拷贝
		SqList(size_type count, const T& val)
		{
			if (count <= 0)
			{
				SqList();
				return;
			}

			_Create_Mem(_Rise_size(count));
			_last = std::uninitialized_fill_n(_first, count, val);
		}

		// 初始化只有一个成员的list
		SqList(const T& val)
		{
			_Create_Mem(LIST_INIT_SIZE);
			_last = std::uninitialized_fill_n(_first, size_type(1), val);
		}

		// 释放所有的内存空间
		~SqList()
		{
			_alloc.deallocate(_first, capacity());
			_first = _end = _last = nullptr;
		}

		// 拷贝构造
		SqList(const SqList& sl)
		{
			_Create_Mem(sl.capacity());
			_last = std::_Uninitialized_copy(sl.begin(), sl.end(), this->_first, _Get_WrapAlloc());
		}

		// 移动构造
		SqList(SqList&& sl) _NOEXCEPT
			: _first(sl._first)
			, _end(sl._end)
			, _last(sl._last)
		{
			sl._first = sl._last = sl._end = nullptr;
		}

		// 列表初始化
		SqList(std::initializer_list<T> paras)
		{
			_Create_Mem(_Rise_size(paras.size()));
			_last = std::_Uninitialized_copy(paras.begin(), paras.end(), _first, _Get_WrapAlloc());
		}

		// copy and move assignment operator
		SqList& operator=(SqList sl)
		{
			swap(*this, sl);
			return *this;
		}

		pointer begin() _NOEXCEPT
		{
			return (this->_first);
		}

		pointer end() _NOEXCEPT
		{
			return (this->_last);
		}

		size_type capacity()
		{
			return (this->_end - this->_first);
		}

		size_type size()
		{
			return (this->_last - this->_first);
		}

		bool empty()
		{
			return (this->_first == this->_last);
		}

		void push_back(const T& val)
		{
			insert(this->end(), val);
		}

		void push_back(T&& val)
		{
			emplace(this->end(), std::move(val));
		}

		void emplace_back(T&& val)
		{
			if (this->_last == this->_end)
				_Reserve(1);
			_alloc.construct(this->_last, std::forward<T>(val));
			this->_last++;
		}

		void push_front(const T& val)
		{
			insert(this->begin(), val);
		}

		void push_front(T&& val)
		{
			insert(this->begin(), std::move(val));
		}

		T pop_back()
		{
			T elem = *(end() - 1);
			erase(end() - 1);
			return elem;
		}

		T pop_front()
		{
			T elem = *(begin());
			erase(begin());
			return elem;
		}

		pointer insert(const pointer where, const T& val)
		{
			return (_Insert_n(where, size_type(1), val));
		}

		template<typename _IteratorType>
		pointer insert(const pointer where, _IteratorType first, _IteratorType last)
		{
			return (_Insert_Range(where, first, last));
		}

		pointer insert(const pointer where, size_type count, const T& val)
		{
			return (_Insert_n(where, count, val));
		}

		pointer insert(const pointer where, std::initializer_list<T> vals)
		{
			return (_Insert_Range(where, vals.begin(), vals.end()));
		}

		pointer insert(const pointer where, T&& val)
		{
			return (emplace(where, std::forward<T>(val)));
		}

		pointer emplace(const pointer where, T&& val)
		{
			emplace_back(std::forward<T>(val));
			std::rotate(where, end() - 1, end());
			return (where);
		}

		pointer erase(const size_type pos)
		{
			return (erase(begin() + pos));
		}

		// 删除where处的元素
		pointer erase(const pointer where)
		{
			std::_Move(where + 1, end(), where);
			_alloc.destroy(this->_last - 1);
			this->_last--;
			return where;
		}

		pointer erase(const pointer first, const pointer last)
		{
			if (first >= end() || this->_first > first || this->_last < last || first > last)
				return pointer();

			if (first == begin() && last == end())
				clear();

			pointer firstArg = first;
			pointer _Ptr = std::_Move(last, end(), first);
			std::_Destroy_range(ptr, end(), _Get_WrapAlloc());
			return firstArg;
		}

		reference at(const size_type pos)
		{
			return *(this->_first + pos);
		}

		reference at(const size_type pos) const
		{
			return *(this->_first + pos);
		}

		// 清空list
		void clear()
		{
			_alloc.deallocate(_first, size());
			_last = _first;
		}

		// 获得某一元素的位置信息, 使用==关系运算符
		size_type localElem(const T& val)
		{
			return _Check_elem(val);
		}

		bool exist(const T& val)
		{
			return (localElem(val) > 0);
		}

		// 对list进行遍历，对所有的元素执行Pred操作
		bool Traverse()
		{
			pointer ptr = _first;
			for (; ptr != _last; ptr++)
			{
				std::cout << *ptr << "\t";
			}

			std::cout << endl;
			
			return true;
		}

		T& operator[](const size_type index)
		{
			return *(this->_first + index);
		}
		const T& operator[](const size_type index) const
		{
			return *(this->_first + index);
		}

		/*
			list union，将另一个SqList并入当前SqList;
			被插入的元素应当和原来的list没有关联，移动或者拷贝
		*/
		SqList& Union(SqList sl)
		{
			T* first = sl._first;
			T* last = sl._first + sl.Size();
			for (; first != last; first++) {
				if (!exist(*first))
					push_back(std::move(*first));
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
		// list位置标记
		pointer _first;
		pointer _last;
		pointer _end;

		std::allocator<T> _alloc;

		std::_Wrap_alloc<std::allocator<T>> _Get_WrapAlloc()
		{
			return std::_Wrap_alloc<std::allocator<T>>(_alloc);
		}

		void _Create_Mem(size_type capacity)
		{
			std::allocator<T> alloc;
			_first = alloc.allocate(capacity);
			_end = _first + capacity;
			_alloc = alloc;
		}

		// copy [first, last) to [dest, ...) where is uninitialized
		// @return: copy success, return where + (last - first)
		pointer _UninitCopy(pointer first, pointer last, pointer dest)
		{
			return (std::_Uninitialized_copy(first, last, dest, _Get_WrapAlloc()));
		}

		// move [first, last) to [dest, ...) where is uninitialized
		pointer _UninitMove(pointer first, pointer last, pointer dest)
		{
			return (std::_Uninitialized_move(first, last, dest, _Get_WrapAlloc()));
		}

		pointer _UninitFill(pointer dest, size_type count, const T* val)
		{
			std::_Uninitialized_fill_n(dest, count, val, _Get_WrapAlloc());
			return (dest + count);
		}

		template<typename _IteratorType>
		pointer _Insert_Range(pointer where, _IteratorType first, _IteratorType last)
		{
			if (first > last || this->_first > where || this->_last < where)
				return (where);

			size_type offset = where - begin();
			size_type count = last - first;
			if (count >= _Unused_capacity())
				// reallocate
			{
				pointer oldFirst = _first;
				pointer oldLast = _last;
				size_type oldCapacity = capacity();

				_Create_Mem(_Grow_to(count));
				pointer ptr = _UninitMove(oldFirst, where, _first);
				ptr = _UninitCopy(first, last, ptr);
				_last = _UninitMove(where, oldLast, ptr);

				std::_Destroy_range(oldFirst, oldLast, _Get_WrapAlloc());
				_alloc.deallocate(oldFirst, oldCapacity);
			}
			else
			{
				_UninitCopy(first, last, this->_last);
				std::rotate(where, this->_last, this->_last + count);
				this->_last += count;
			}

			return (begin + offset);
		}

		pointer _Insert_n(pointer where, size_type count, const T& val)
		{
			size_type offset = where - begin();
			if (this->_first > where || this->_last < where)
				return (where);

			if (count <= 0)
				;
			else if (_Unused_capacity() < count)
				// reallocate
			{
				pointer oldFirst = this->_first;
				pointer oldLast = this->_last;
				size_type oldCapacity = capacity();
				T tmpVal = val;

				_Create_Mem(_Grow_to(count));
				_UninitMove(oldFirst, where, this->_first);
				_UninitFill(this->_first + offset, count, std::addressof(tmpVal));
				_UninitMove(where, oldLast, this->_first + offset + count);

				std::_Destroy_range(oldFirst, oldLast, _Get_WrapAlloc());
				_alloc.deallocate(oldFirst, oldCapacity);
			}
			else if (this->_last - where < count)
			{
				T tmpVal = val;

				_UninitMove(where, this->_last, this->_last + count);
				_UninitFill(this->_last, count - (this->_last - where), std::addressof(tmpVal));
				std::fill(where, this->_last, tmpVal);
				this->_last += count;
			}
			else
			{
				pointer oldLast = this->_last;
				this->_last = _UninitMove(oldLast - count, oldLast, oldLast);
				std::_Copy_backward(where, oldLast - count, oldLast);
				std::fill(where, where + count, val);
			}
			return (begin() + offset);
		}

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

		// 返回未使用的容量大小>
		size_type _Unused_capacity() const _NOEXCEPT
		{
			return _end - _last;
		}

		// 容量增长
		void _Reallocate(const size_type newCapacity)
		{
			pointer first = begin();
			pointer last = end();
			size_type oldCapacity = capacity();
			_Create_Mem(newCapacity);
			std::_Wrap_alloc<std::allocator<T>> wrap_alloc(_alloc);
			_last = std::_Uninitialized_move(first, last, _first, wrap_alloc);
			_alloc.deallocate(first, oldCapacity);
		}

		// 确定是否有足够的空间
		void _Reserve(const size_type count)
		{
			if (count < _Unused_capacity())
				return;
			else if (count > _Unused_capacity())
				_Reallocate(_Grow_to(count));
		}

		size_type _Grow_to(size_type count)
		{
			size_type newSize = _Rise_size(capacity());
			if (count > newSize - size())
				newSize = capacity() + count;
			return newSize;
		}

		// 定义容量增长的方式
		size_type _Rise_size(const size_type count) const _NOEXCEPT
		{
			return count + count / 2;
		}
	};

}