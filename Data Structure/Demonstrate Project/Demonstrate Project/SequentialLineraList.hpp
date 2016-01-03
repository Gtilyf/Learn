/*
	���Ա��˳��ʵ�֣��ڴ���Ʋ���allocatorʵ��.

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

		// ��ʼ��n����ͬ��Ԫ�أ���Ԫ�ؽ��п���
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

		// ��ʼ��ֻ��һ����Ա��list
		SqList(const T& data, bool order = false)
			: _capacity(LIST_INIT_SIZE)
			, _length(1)
			, _isOrdered(order)
		{
			std::allocator<T> alloc;

			_base = alloc.allocate(LIST_INIT_SIZE);
			alloc.construct(_base, data);
		}

		// �ͷ����е��ڴ�ռ�
		~SqList()
		{
			std::allocator<T> alloc;
			alloc.deallocate(_base, _capacity);
			_base = nullptr;
			_capacity = 0;
			_length = 0;
		}

		// ��������
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

		// �ƶ�����
		SqList(SqList&& sl) _NOEXCEPT
			: _capacity(std::move(sl._capacity))
			, _base(std::move(sl._base))
			, _length(std::move(sl._length))
			, _isOrdered(sl._isOrdered)
		{
			sl._base = nullptr;
		}

		// �б��ʼ��
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

		// ���list���ڴ�ռ䱣��
		void Clear()
		{
			std::allocator<T> alloc;

			T* p = _base;
			for (; _length > 0; _length--)
				alloc.destroy(p++);
		}

		// ɾ��Ԫ�أ����ظ�Ԫ�صı���
		T Remove(const size_type index)
		{
			T* p = _base + index;
			T rtval = std::move(*p);
			p = nullptr;

			_Move_forward(index + 1);
			_length--;
			return rtval;
		}

		// ���ĳһԪ�ص�λ����Ϣ, ʹ��==��ϵ�����
		size_type LocalElem(const T& data)
		{
			return _Check_elem(data);
		}

		bool Exist(const T& data)
		{
			return (LocalElem(data) > 0);
		}

		// ����Ԫ�ص�ǰ�����������Ԫ�أ��򷵻�βԪ��
		T& PriorElem(const T& data)
		{
			int local = LocalElem(data);

			if (local > 0)
				return *this[local - 1];
			else
				return *this[_length - 1];
		}

		// ����Ԫ�صĺ�̣������βԪ�أ��򷵻���Ԫ��
		T& NextElem(const T& data)
		{
			int local = LocalElem(data);

			if (local < _length - 1)
				return *this[local + 1];
			else
				return *this[0];
		}

		// copy����Ԫ��
		bool Insert(const size_type index, const T& data)
		{
			_Reserve(1);
			_Move_back(index);
			*(_base + index) = data;
			_length++;
			return true;
		}

		// move����Ԫ��
		bool Insert(const size_type index, T&& data)
		{
			_Reserve(1);
			_Move_back(index);
			*(_base + index) = std::move(data);
			_length++;
			return true;
		}

		// ��listβ������(copy)
		bool BackInsert(const T& data)
		{
			return Insert(_length, data);
		}

		// ��listβ������(move)
		bool BackInsert(T&& data)
		{
			return Insert(_length, std::move(data));
		}

		// ��listͷ������(copy)
		bool FrontInsert(const T& data)
		{
			return Insert(0, data);
		}

		// ��listͷ������(move)
		bool FrontInsert(T&& data)
		{
			return Insert(0, std::move(data));
		}

		// ��list���б����������е�Ԫ��ִ��Pred����
		bool Traverse(bool (*Pred) (T&))
		{
			for (int i = 0; i < Size(); i++)
			{
				if (!Pred(*(_base + i)))
					return false;
			}
			return true;
		}

		// Ԫ�ط��ʣ����ظ�Ԫ�ص�����
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
			list union������һ��SqList���뵱ǰSqList;
			�������Ԫ��Ӧ����ԭ����listû�й������ƶ����߿���
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
			list Merge, �����µ�SqList������SqList��Ԫ�ز����µ�SqList
			�������Ԫ��Ӧ����ԭ����listû�й������ƶ����߿���
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
		// listĬ�ϳ�ʼ����
		const size_type LIST_INIT_SIZE = 10;
		// list��ǰ����
		int _capacity;
		// listԪ�ػ�ַ
		T* _base;
		// Ԫ�س���
		int _length;
		// list�Ƿ�����
		bool _isOrdered;

		// ���Ԫ���Ƿ����
		// TODO: ʹ��algorithms find����Ԫ��
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

		// ����±��Ƿ�Ϸ�
		bool _Is_legel(const size_type index)
		{
			return index > 0 && index < Size();
		}

		// ����δʹ�õ�������С>
		size_type _Unused_capacity() const _NOEXCEPT
		{
			return _capacity - _length;
		}

		// ��������
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

		// ȷ���Ƿ����㹻�Ŀռ�
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

		// �������������ķ�ʽ
		size_type _Rise_size(const size_type count) const _NOEXCEPT
		{
			return count + count / 2;
		}

		// ����iλ��֮���Ԫ����������ƶ�[index, _length)
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

		// ����iλ��֮���Ԫ��������ǰ�ƶ�[index, _length)
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