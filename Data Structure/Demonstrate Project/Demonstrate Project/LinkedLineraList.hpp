/*
	���Ա������ʵ�֣��ڴ���Ʋ���allocatorʵ��
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
		// Ĭ�ϳ�ʼ����ֻ����һ��tail�ڵ�
		LinkedList()
			: _head(nullptr)
			, _tail(new node_type())
			, _length(0)
		{ }

		// �б��ʼ��
		LinkedList(std::initializer_list<T> paras)
			: _tail(new node_type())
			, _length(paras.size())
		{
			_Build_List(paras.begin(), paras.end());
		}

		// ��ʼ������n����ͬ��Ԫ��elem��list
		LinkedList(const T& elem, size_type count)
			: _tail(new node_type())
			, _length(count)
		{
			_Build_List(elem, count);
		}

		// ��ʼ��ֻ����һ��Ԫ�ص�list
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

		// ������е�Ԫ��
		void Clear()
		{
			for (; _head != _tail; _head = _head->next)
				delete _head;
		}

		// ɾ��Ԫ�أ����ظ�Ԫ�صı��ݣ�����ֵ�����ƶ�
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

		// ���ĳһԪ�ص�λ����Ϣ, ʹ��==��ϵ�����
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

		// ������β�ڵ㴦���һ���ڵ�
		bool Append(LinkedNode<T>*);

		// ��list���б����������е�Ԫ��ִ��ָ������
		bool Traverse();

		// list union������һ��LinkedList���뵱ǰLinkedList;
		// �������Ԫ��Ӧ����ԭ����listû�й������ƶ����߿���
		LinkedList& Union(LinkedList);
		LinkedList& operator+=(LinkedList);

		// list Merge, �����µ�LinkedList������LinkedList��Ԫ�ز����µ�LinkedList
		// �������Ԫ��Ӧ����ԭ����listû�й������ƶ����߿���
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

		// �����ڵ㣬���������Լ�����ǰ��������ϵ
		void _Create_Node(const T& data, node_type*& piror, node_type*& curr)
		{
			curr = new node_type(data, piror);
			piror->next = curr;
			piror = curr;
		}

		// ��begin() - end()��������ݽ�������
		template<typename _Lnlt>
		void _Build_List(_Lnlt first, _Lnlt last)
		{
			_head = new node_type(*first);
			node_type* prior = _head;
			node_type* curr;
			std::for_each(first, last, [&](const T& elem) -> void { _Create_Node(elem, prior, curr); });
			curr->next = _tail;
		}

		// ��n����ͬԪ�ؽ��������n���ڵ�
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