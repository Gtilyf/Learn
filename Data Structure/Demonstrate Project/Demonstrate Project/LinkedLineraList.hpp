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
		return (ln1.data == ln2.data && ln1.next == ln2.next && ln1.prior == ln2.prior);
	}

	template<typename T>
	struct LinkedNode
	{
		LinkedNode()
			: next(nullptr)
			, prior(nullptr)
		{ }

		LinkedNode(const T& elem, LinkedNode* p = nullptr, LinkedNode* n = nullptr)
			: data(elem)
			, next(n)
			, prior(p)
		{ }

		~LinkedNode()
		{
			next = nullptr;
			prior = nullptr;
		}

		T data;
		LinkedNode* next;
		LinkedNode* prior;

		friend bool operator== <>(const LinkedNote<T>&, const LinkedNote<T>&);
	};

	template<typename T>
	class LinkedList{

		typedef int size_type;
		typedef LinkedNode<T> node_type;

	public:
		// 默认初始化，只含有一个tail节点
		LinkedList()
			: _head(nullptr)
			, _tail(new node_type())
			, _length(0)
		{ }

		// 列表初始化
		LinkedList(std::initializer_list<T> paras)
			: _tail(new node_type())
			, _length(paras.size())
		{
			_Build_List(paras.begin(), paras.end());
		}

		// 初始化含有n个相同的元素elem的list
		LinkedList(const T& elem, size_type count)
			: _tail(new node_type())
			, _length(count)
		{
			_Build_List(elem, count);
		}

		// 初始化只含有一个元素的list
		LinkedList(const T& elem)
			: _tail(new LinkedNode<T>())
		{
			_head = new LinkedNode<T>(elem, nullptr, _tail);
			_length = 1;
		}

		~LinkedList()
		{
			Clear();
			delete _tail;
		}

		// copy constructor
		LinkedList(const LinkedList& ll)
			: _tail(new node_type())
			, _length(ll._length)
		{
			node_type* source = ll._head;
			_head = new node_type(source->data);
			node_type* proir = _head;
			node_type* curr;
			while (source != ll._tail){
				curr = new node_type(source->data, proir);
				proir->next = curr;
				proir = curr;
				source = source->next;
			}
			curr->next = _tail;
		}

		// move consttructor
		LinkedList(LinkedList&& ll) _NOEXCEPT
			: _head(ll._head)
			, _tail(ll._tail)
			, _length(ll._length)
		{
			ll._head = ll._tail = nullptr;
		}

		// copy and move assignment operator
		LinkedList& operator=(LinkedList ll)
		{
			swap(*this, ll);
			return *this;
		}

		bool Empty()
		{
			return (0 == _length);
		}

		// 清除所有的元素
		void Clear()
		{
			for (; _head != _tail; _head = _head->next)
				delete _head;
		}

		// 删除元素，返回该元素的备份，返回值优先移动
		T Remove(const size_type& index)
		{
			node_type* curr = _head;
			while (inde-- != 0)
				curr = curr->next;

			curr->prior->next = curr->next;
			curr->next->prior = curr->prior;
			T data = std::move(curr->data);
			delete curr;

			return data;
		}

		// 获得某一元素的位置信息, 使用==关系运算符
		size_type LocalElem(const T&)
		{

		}

		T& PriorElem(const T& elem)
		{
			size_type pos = LocalElem(elem);
			
			return this->operator[LocalElem(elem) + 1];
		}
		T& NextElem(const T& elem)
		{
			return this->operator[LocalElem(elem) - 1];
		}

		// copy insert
		void Insert(size_type pos, const T& elem)
		{
			
		}

		// move insert
		void Insert(size_type pos, T&& elem)
		{

		}
		void BackInsert(T&&)
		{

		}
		void FrontInsert(T&&)
		{

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
		LinkedNode<T>* _head;
		LinkedNode<T>* _tail;
		size_type _length;

		// 建立节点，包括数据以及与其前后驱的联系
		void _Create_Node(const T& data, node_type*& piror, node_type*& curr)
		{
			curr = new node_type(data, piror);
			piror->next = curr;
			piror = curr;
		}

		// 由begin() - end()区间的数据建立链表
		template<typename _Lnlt>
		void _Build_List(_Lnlt first, _Lnlt last)
		{
			_head = new node_type(*first);
			node_type* prior = _head;
			node_type* curr;
			std::for_each(first, last, [&](const T& elem) -> void { _Create_Node(elem, prior, curr); });
			curr->next = _tail;
		}

		// 由n个相同元素建立链表的n个节点
		void _Build_List(const T& elem, size_type count)
		{
			_head = new node_type(elem);
			node_type* prior = _head;
			node_type* curr;
			while (--count > 0)
				_Create_Node(elem, prior, curr);
			curr->next = _tail;
		}

		bool Check(const T&);
	};
}