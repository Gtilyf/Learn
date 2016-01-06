/*
	线性表的链表实现，内存控制采用allocator实现
*/

#include <memory>
#include <stdexcept>
#include <algorithm>

#include <iostream>

namespace DS
{
	template<typename T>
	class LinkedList;

	template<typename T>
	class LinkedNote;

	template<typename T>
	void swap(LinkedList<T>& la, LinkedList<T>& lb)
	{
		using namespace std::swap;
		swap(la._head, lb._head);
		swap(la._length, lb._length);
	}

	template<typename T>
	LinkedList<T> operator+(LinkedList<T> la, LinkedList<T> lb)
	{
		la += std::move(lb);
		return la;
	}

	template<typename T>
	bool operator==(const LinkedList<T>& la, const LinkedList<T>& lb)
	{
		return (la._head == lb._head && la._length == lb._length);
	}

	template<typename T>
	bool operator!=(const LinkedList<T>& la, const LinkedList<T>& lb)
	{
		return !(la == lb)
	}

	template<typename T>
	bool operator>(const LinkedList<T>& la, const LinkedList<T>& lb)
	{
		return (la._length > lb._length);
	}

	template<typename T>
	bool operator<(const LinkedList<T>& la, const LinkedList<T>& lb)
	{
		return !(la > lb);
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

		

	public:
		typedef std::size_t size_type;
		typedef LinkedNode<T> node_type;
		typedef LinkedNode<T>* pointer;

		// 默认初始化，只含有一个tail节点
		LinkedList()
			: _head(_Create_head())
			, _length(0)
		{ }

		// 列表初始化
		LinkedList(std::initializer_list<T> paras)
		{
			_Consturct_List(paras.begin(), paras.end());
		}

		// 初始化含有n个相同的元素elem的list
		LinkedList(const T& elem, size_type count)
		{
			_Consturct_List(elem, count);
		}

		// 初始化只含有一个元素的list
		LinkedList(const T& elem)
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
		{
			_head = _Create_head();
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
			return (this->_Next_node(_head));
		}

		size_type size()
		{
			return _lenght;
		}

		bool empty()
		{
			return (_Next_node(_head) == _head);
		}

		// 清除所有的元素
		void clear()
		{
			erase(begin(), end());
		}

		pointer erase(const pointer where)
		{
			pointer ptr = _Unlinked_node(where);
			delete where;
			return (ptr);
		}

		pointer erase(pointer first, pointer last)
		{
			while (first != last)
				first = erase(first);

			return (last);
		}

		pointer push_back(const T& val)
		{
			return (insert(end(), val));
		}

		pointer push_back(T&& rval)
		{
			return (emplace(end(), std::forward<T>(rval)));
		}

		pointer emplace_back(T&& rval)
		{
			return (emplace(end(), std::forward<T>(rval)));
		}

		pointer push_front(const T& val)
		{
			return (insert(begin(), val));
		}

		pointer push_front(T&& rval)
		{
			return (emplace(begin(), std::forward<T>(rval)));
		}

		T pop_back()
		{
			T rtVal = _Prev_node(end())->data;
			erase(_Prev_node(end()));
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
			return (_Prev_node(end())->data);
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
			return (emplace(where, std::forward<T>(val)));
		}

		pointer emplace(pointer where, T&& rval)
		{
			pointer newNode = _Create_node(std::move(rval), _Prev_node(where), where);
			_Prev_node(where)->next = newNode;
			where->prev = newNode;
			_length++;
			return _Prev_node(where);
		}

		// 在链表尾节点处添加一串节点
		void Append(pointer node)
		{
			
		}

		// 对list进行遍历，对所有的元素执行指定操作
		bool Traverse()
		{
			pointer ptr = begin();
			for (; ptr != end(); ptr = _Next_node(ptr))
				std::cout << ptr->data << "\t";

			std::cout << endl;

			return true;
		}

		// list union，将另一个LinkedList并入当前LinkedList;
		// 被插入的元素应当和原来的list没有关联，移动或者拷贝
		LinkedList& Union(LinkedList ll)
		{
			return *this;
		}

		LinkedList& operator+=(LinkedList ll)
		{
			return this->Union(std::move(ll));
		}

		// list Merge, 返回新的LinkedList，两个LinkedList的元素并入新的LinkedList
		// 被插入的元素应当和原来的list没有关联，移动或者拷贝
		LinkedList Merge(LinkedList la, LinkedList lb)
		{
			return la + lb;
		}
		friend LinkedList operator+ <>(LinkedList, LinkedList);

		friend bool operator== <>(const LinkedList&, const LinkedList&);
		friend bool operator!= <>(const LinkedList&, const LinkedList&);
		friend bool operator> <>(const LinkedList&, const LinkedList&);
		friend bool operator< <>(const LinkedList&, const LinkedList&);

		friend void swap <>(LinkedList&, LinkedList&);

	private:
		pointer _head;
		size_type _length;

		pointer& _Prev_node(const pointer node)
		{
			return (node->prev);
		}

		pointer& _Next_node(const pointer node)
		{
			return (node->next);
		}

		pointer _Create_node(pointer prev, pointer next)
		{
			std::allocator<node_type> alloc;
			pointer node = alloc.allocate(1);
			if (prev == pointer())
			{
				prev = node;
				next = node;
			}
			alloc.construct(std::addressof(node->prev), prev);
			alloc.construct(std::addressof(node->next), next);

			return node;
		}

		// 建立节点，包括数据以及与其前后驱的联系
		pointer _Create_node(const T& data, pointer prev, pointer next)
		{
			std::allocator<T> alloc;
			pointer node = _Create_node(prev, next);
			alloc.construct(std::addressof(node->data), data);
			return node;
		}

		pointer _Create_node(T&& data, pointer prev, pointer next)
		{
			std::allocator<T> alloc;
			pointer node = _Create_node(prev, next);
			alloc.construct(std::addressof(node->data), std::forward<T>(data));
			
			return node;
		}

		pointer _Create_head()
		{
			T elem;
			return _Create_node(elem , pointer(), pointer());
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
			pointer newNode = _Create_node(val, _Prev_node(where), where);
			_Prev_node(where)->next = newNode;
			where->prev = newNode;
			_length++;
			return newNode;
		}

		template<typename _IteratorType>
		pointer _Insert_range(_IteratorType first, _IteratorType last, pointer where)
		{
			if (first > last)
				return (where);

			pointer ptr = _Prev_node(where);
			for (; first != last; first++)
				_Insert(where, *first);

			return _Next_node(ptr);
		}

		pointer _Insert_n(pointer where, size_type count, const T& val)
		{
			if (count <= 0)
				return (where);

			pointer ptr = _Prev_node(where);
			for (; count > 0; count--)
				_Insert(where, val);

			return _Next_node(ptr);
		}

		pointer _Unlinked_node(pointer node)
		{
			_Prev_node(node)->next = _Next_node(node);
			_Next_node(node)->prev = _Prev_node(node);

			return _Next_node(node);
		}
	};
}