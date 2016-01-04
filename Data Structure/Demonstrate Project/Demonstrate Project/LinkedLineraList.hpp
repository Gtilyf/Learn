/*
	线性表的链表实现，内存控制采用allocator实现
*/

#include <memory>
#include <stdexcept>
#include <algorithm>

namespace DS
{
	template<typename T>
	class LinkedList;

	template<typename T>
	class LinkedNote;

	template<typename T>
	void swap(LinkedList<T>&, LinkedList<T>&)
	{

	}

	template<typename T>
	LinkedList<T> operator+(const LinkedList<T>&, const LinkedList<T>&)
	{

	}

	template<typename T>
	bool operator==(const LinkedList<T>&, const LinkedList<T>&)
	{

	}

	template<typename T>
	bool operator!=(const LinkedList<T>&, const LinkedList<T>&)
	{

	}

	template<typename T>
	bool operator>(const LinkedList<T>&, const LinkedList<T>&)
	{

	}

	template<typename T>
	bool operator<(const LinkedList<T>&, const LinkedList<T>&)
	{

	}

	template<typename T>
	bool operator==(const LinkedNote<T>& ln1, const LinkedNote<T>& ln2)
	{
		return (ln1.data == ln2.data && ln1.next == ln2.next && ln1.prev == ln2.prev);
	}

	template<typename T>
	struct LinkedNode
	{
		typedef LinkedNode* pointer;

		LinkedNode()
			: next(pointer())
			, prev(pointer())
		{ }

		LinkedNode(const T& elem, pointer p = pointer(), pointer n = pointer())
			: data(elem)
			, next(n)
			, prev(p)
		{ }

		LinkedNode(T&& elem, pointer p = pointer(), pointer n = pointer())
			: data(std::move(elem))
			, next(n)
			, prev(p)
		{

		}

		~LinkedNode()
		{
			next = nullptr;
			prev = nullptr;
		}

		T data;
		pointer next;
		pointer prev;

		friend bool operator== <>(const LinkedNote<T>&, const LinkedNote<T>&);
	};

	template<typename T>
	class LinkedList {

		typedef std::size_t size_type;
		typedef LinkedNode<T> node_type;
		typedef LinkedNode<T>* pointer;

	public:
		// 默认初始化，只含有一个tail节点
		LinkedList()
			: _head(_Create_head())
			, _length(0)
		{ }

		// 列表初始化
		LinkedList(std::initializer_list<T> paras)
			: _length(paras.size())
		{
			_Consturct_List(paras.begin(), paras.end());
		}

		// 初始化含有n个相同的元素elem的list
		LinkedList(const T& elem, size_type count)
			: _length(count)
		{
			_Consturct_List(elem, count);
		}

		// 初始化只含有一个元素的list
		LinkedList(const T& elem)
			: _length(1)
		{
			_Consturct_List(elem, 1);
		}

		~LinkedList()
		{
			clear();
			delete _head;
		}

		// copy constructor
		LinkedList(const LinkedList& ll)
			: _length(ll._length)
		{
			_Create_head();
			pointer first = ll._head->next;
			for (; first != ll._head; first = first->next)
				push_back(first->data);
		}

		// move consttructor
		LinkedList(LinkedList&& ll) _NOEXCEPT
			: _head(ll._head)
			, _length(ll._length)
		{
			ll._head = _Create_head();
		}

		// copy and move assignment operator
		LinkedList& operator=(LinkedList ll)
		{
			swap(*this, ll);
			return *this;
		}

		pointer end()
		{
			return (_head);
		}

		pointer begin()
		{
			return (this->_Next_Node(_head));
		}

		size_type size()
		{
			return _lenght;
		}

		bool empty()
		{
			return (_Next_Node(_head) == _head);
		}

		// 清除所有的元素
		void clear()
		{
			erase(begin(), end());
		}

		pointer erase(const pointer where)
		{
			pointer ptr _Unlinked_node(where);
			delete where;
			return (ptr);
		}

		pointer erase(const pointer first, const pointer last)
		{
			while (first != last)
				first = erase(first);

			return (last);
		}

		pointer push_back(const T& val)
		{
			insert(end(), val);
		}

		pointer push_back(T&& rval)
		{
			emplace(end(), std::forward(rval));
		}

		pointer emplace_back(T&& rval)
		{
			emplace(end(), std::forward(rval));
		}

		pointer push_front(const T& val)
		{
			insert(begin(), val);
		}

		pointer push_front(T&& rval)
		{
			emplace(begin(), std::forward(rval));
		}

		T pop_back()
		{
			T rtVal = _Prev_Node(end())->data;
			erase(ptr);
			return rtVal;
		}

		T pop_front()
		{
			T rtVal = begin()->data;
			erase(begin());
			return rtVal;
		}

		T& front()
		{
			return (begin()->data);
		}

		T& back()
		{
			return (_Prev_Node(end())->data);
		}

		pointer insert(pointer where, const T& val)
		{
			return (_Insert(where, val));
		}

		template<typename _IteratorType>
		pointer insert(_IteratorType first, _IteratorType last, pointer where)
		{
			return (_Insert_range(first, last, where));
		}

		pointer insert(pointer where, size_type count, const T& val)
		{
			return (_Insert_n(where, count, val));
		}

		pointer insert(pointer where, std::initializer_list<T> vals)
		{
			return (_Insert_range(vals.begin(), vals.end(), where));
		}

		pointer insert(pointer where, T&& val)
		{
			return (emplace(where, std::forward(val)));
		}

		pointer emplace(pointer where, T&& rval)
		{
			_Create_Node(std::move(rval), _Prev_Node(where), _Next_Node(where));
			_length++;
			return _Prev_Node(where);
		}

		// 在链表尾节点处添加一串节点
		bool Append(LinkedNode<T>*);

		// 对list进行遍历，对所有的元素执行指定操作
		bool Traverse();

		// list union，将另一个LinkedList并入当前LinkedList;
		// 被插入的元素应当和原来的list没有关联，移动或者拷贝
		LinkedList& Union(LinkedList);
		LinkedList& operator+=(LinkedList);

		// list Merge, 返回新的LinkedList，两个LinkedList的元素并入新的LinkedList
		// 被插入的元素应当和原来的list没有关联，移动或者拷贝
		LinkedList Merge(LinkedList, LinkedList);
		friend LinkedList operator+ <>(LinkedList, LinkedList);

		friend bool operator== <>(const LinkedList&, const LinkedList&);
		friend bool operator!= <>(const LinkedList&, const LinkedList&);
		friend bool operator> <>(const LinkedList&, const LinkedList&);
		friend bool operator< <>(const LinkedList&, const LinkedList&);

		friend void swap <>(LinkedList&, LinkedList&);

	private:
		pointer _head;
		size_type _length;

		pointer& _Prev_Node(const pointer node)
		{
			return (node->prev);
		}

		pointer& _Next_Node(const pointer node)
		{
			return (node->next);
		}

		// 建立节点，包括数据以及与其前后驱的联系
		pointer _Create_Node(const T& data, pointer prev, pointer next)
		{
			pointer node = pointer();
			if (prev == pointer())
			{
				prev = node;
				next = node;
			}
			node = new node_type(data, prev, next);
			return node;
		}

		pointer _Create_Node(T&& data, pointer prev, pointer next)
		{
			pointer node = pointer();
			if (prev == pointer())
			{
				prev = node;
				next = node;
			}
			node = new node_type(std::move(data), prev, next);
			return node;
		}

		pointer _Create_head()
		{
			return _Create_Node(T(), pointer(), pointer());
		}

		// 由begin() - end()区间的数据建立链表
		template<typename _Lnlt>
		void _Consturct_List(_Lnlt first, _Lnlt last)
		{
			_head = _Create_head();
			std::for_each(first, last, [&](const T& elem) -> void { push_back(elem); });
		}

		// 由n个相同元素建立链表的n个节点
		void _Consturct_List(const T& elem, size_type count)
		{
			_head = _Create_head();
			while (--count > 0)
				push_back(elem);
		}

		pointer _Insert(pointer where, const T& val)
		{
			pointer newNode = _Create_Node(val, _Prev_Node(where), _Next_Node(where));
			_Prev_Node(where)->next = newNode;
			where->prev = newNode;

			return newNode;
		}

		template<typename _IteratorType>
		pointer _Insert_range(_IteratorType first, _IteratorType last, pointer where)
		{
			if (first > last)
				return (where);

			pointer ptr = _Prev_Node(where);
			for (; first != last; first++)
				_Insert(where, *first);

			return _Next_Node(ptr);
		}

		pointer _Insert_n(pointer where, size_type count, const T& val)
		{
			if (count <= 0)
				return (where);

			_length += count;
			pointer ptr = _Prev_Node(where);
			for (; count > 0; count--)
				_Insert(where, val);

			return _Next_Node(ptr);
		}

		pointer _Unlinked_node(pointer node)
		{
			_Prev_Node(node)->next = _Next_Node(node);
			_Next_Node(node)->prev = _Prev_Node(node);

			return _Next_Node(node);
		}
	};
}