/*
	���Ա��˳��ʵ�֣��ڴ���Ʋ���allocatorʵ��
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
		///	��ʼ��n����ͬ��Ԫ�أ���Ԫ�ؽ��п���
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
		///	��ʼ��ֻ��һ����Ա��list�������ƶ�Ԫ��
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
		///	�ͷ����е��ڴ�ռ�
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
		///	��������
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
		///	�ƶ�����
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
		/// �б��ʼ��
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
		///	���list���ڴ�ռ䱣��
		/// </summary>
		bool Clear()
		{
			std::allocator<T> alloc;

			T* p = _base;
			while (_length-- > 0)
				alloc.destroy(p++);
		}

		/// <summary>
		///	ɾ��Ԫ�أ����ظ�Ԫ�صı���
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
		///	���ĳһԪ�ص�λ����Ϣ, ʹ��==��ϵ�����
		/// </summary>
		SIZE_TYPE LocalElem(const T& data)
		{
			return _Check_elem(data);
		}

		/// <summary>
		///	����Ԫ�ص�ǰ�����������Ԫ�أ��򷵻�βԪ��
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
		///	����Ԫ�صĺ�̣������βԪ�أ��򷵻���Ԫ��
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
		///	copy����Ԫ��
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
		/// move����Ԫ��
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
		///	��listβ������(copy)
		/// </summary>
		bool BackInsert(const T& data)
		{
			return Insert(_length, data);
		}

		/// <summary>
		///	��listβ������(move)
		/// </summary>
		bool BackInsert(T&& data)
		{
			return Insert(_length, std::move(data));
		}

		/// <summary>
		///	��listͷ������(copy)
		/// </summary>
		bool FrontInsert(const T& data)
		{
			return Insert(0, data);
		}

		/// <summary>
		/// ��listͷ������(move)
		/// </summary>
		bool FrontInsert(T&& data)
		{
			return Insert(0, std::move(data));
		}

		/// <summray>
		///	��list���б����������е�Ԫ��ִ��ָ������
		/// </summary>
		/// <param name="visitor">��Ԫ��ָ���Ĳ���</param>
		/// <returns>�����ɹ����</returns>
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
		///	Ԫ�ط��ʣ����ظ�Ԫ�ص�����
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
		///	list union������һ��SqList���뵱ǰSqList;
		/// �������Ԫ��Ӧ����ԭ����listû�й������ƶ����߿���
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
		///	list Merge, �����µ�SqList������SqList��Ԫ�ز����µ�SqList
		/// �������Ԫ��Ӧ����ԭ����listû�й������ƶ����߿���
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
		// listĬ�ϳ�ʼ����
		const SIZE_TYPE LIST_INIT_SIZE = 10;
		// list��ǰ����
		int _capacity;
		// listԪ�ػ�ַ
		T* _base;
		// Ԫ�س���
		int _length;
		// list�Ƿ�����
		bool _isOrdered;

		/// <summary>
		///	���Ԫ���Ƿ����
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
		///	����±��Ƿ�Ϸ�
		/// </summary>
		bool _Is_legel(SIZE_TYPE i)
		{
			return i > 0 && i < Size();
		}

		/// <summary>
		///	����δʹ�õ�������С
		/// </summary>
		SIZE_TYPE _Unused_capacity() const _NOEXCEPT
		{
			return _capacity - _length;
		}

		/// <summary>
		///	��������
		/// </summary>
		/// @count: ������
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
		///	ȷ���Ƿ����㹻�Ŀռ�
		/// </summary>
		/// @count: ��Ҫ������
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
		///	�������������ķ�ʽ
		/// </summary>
		SIZE_TYPE _Rise_size(SIZE_TYPE count) const _NOEXCEPT
		{
			return count + count / 2;
		}

		/// <summary>
		/// ����iλ��֮���Ԫ����������ƶ�
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
		///	����iλ��֮���Ԫ��������ǰ�ƶ�
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