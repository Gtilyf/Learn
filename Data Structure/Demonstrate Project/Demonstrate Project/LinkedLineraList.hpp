/*
���Ա������ʵ�֣��ڴ���Ʋ���shared_ptrʵ��
*/

//#include <memory>
//#include <stdexcept>
//
//template <typename T>
//struct LinkedNode
//{
//	T data;
//	LinkedNode* next;
//	LinkedNode* prior;
//};
//
//template <typename T>
//class LinkedList{
//public:
//	int length;
//
//	LinkedList();
//	LinkedList(initializer_list<T> list);
//	LinkedList(const T&, int);
//	LinkedList(const T&);
//
//	~LinkedList();
//	LinkedList(const LinkedList&);
//	LinkedList(LinkedList&&) _NOEXCEPT;
//
//	/// <summary>
//	/// copy and move assignment operator
//	/// </summary>
//	LinkedList& operator=(LinkedList);
//
//	bool Empty();
//	bool Clear();
//
//	/// <summary>
//	///	ɾ��Ԫ�أ����ظ�Ԫ�صı��ݣ�����ֵ�����ƶ�
//	/// </summary>
//	T Remove(const int);
//
//	/// <summary>
//	///	���ĳһԪ�ص�λ����Ϣ, ʹ��==��ϵ�����
//	/// </summary>
//	/// <returns>����Ԫ����list�е�λ�ã�����������򷵻�-1</returns>
//	int LocalElem(const T&);
//
//	T& PriorElem(const T&);
//	T& NextElem(const T&);
//
//	/// <summary>
//	///	�����ƶ���û���ƶ��򿽱�
//	/// </summary>
//	bool Insert(const int, T&&);
//	bool BackInsert(T&&);
//	bool FrontInsert(T&&);
//
//	/// <summary>
//	///	������β�ڵ㴦���һ���ڵ�
//	/// </summary>
//	bool Append(LinkedNode*);
//
//	/// <summray>
//	///	��list���б����������е�Ԫ��ִ��ָ������
//	/// </summary>
//	/// <param name="visitor">��Ԫ��ָ���Ĳ���</param>
//	/// <returns>�����ɹ����</returns>
//	bool Traverse();
//
//	/// <summary>
//	///	Ԫ�ط���
//	/// </summary>
//	T& GetElem(int);
//	T& operator[](int);
//	const T& operator[](int) const;
//
//	/// <summary>
//	///	list union������һ��LinkedList���뵱ǰLinkedList;
//	/// �������Ԫ��Ӧ����ԭ����listû�й������ƶ����߿���
//	/// </summary>
//	LinkedList& Union(LinkedList);
//	LinkedList& operator+=(LinkedList);
//
//	/// <summary>
//	///	list Merge, �����µ�LinkedList������LinkedList��Ԫ�ز����µ�LinkedList
//	/// �������Ԫ��Ӧ����ԭ����listû�й������ƶ����߿���
//	/// </summary>
//	LinkedList Merge(LinkedList, LinkedList);
//	friend LinkedList operator+ <>(LinkedList, LinkedList);
//
//	friend bool operator== <>(const LinkedList&, const LinkedList&);
//	friend bool operator!= <>(const LinkedList&, const LinkedList&);
//	friend bool operator> <>(const LinkedList&, const LinkedList&);
//	friend bool operator< <>(const LinkedList&, const LinkedList&);
//
//	friend void swap<>(LinkedList&, LinkedList&);
//
//private:
//	LinkedNode<T>* base_elem;
//
//	bool Check(const T&);
//};
//
//template <typename T>
//inline
//void swap(LinkedList<T>&, LinkedList<T>&);
//
//template <typename T>
//LinkedList<T> operator+(const LinkedList<T>&, const LinkedList<T>&);
//
//template <typename T>
//bool operator==(const LinkedList<T>&, const LinkedList<T>&);
//
//template <typename T>
//bool operator!=(const LinkedList<T>&, const LinkedList<T>&);
//
//template <typename T>
//bool operator>(const LinkedList<T>&, const LinkedList<T>&);
//
//template <typename T>
//bool operator<(const LinkedList<T>&, const LinkedList<T>&);