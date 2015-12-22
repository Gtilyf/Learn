/*
线性表的链表实现，内存控制采用shared_ptr实现
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
//	///	删除元素，返回该元素的备份，返回值优先移动
//	/// </summary>
//	T Remove(const int);
//
//	/// <summary>
//	///	获得某一元素的位置信息, 使用==关系运算符
//	/// </summary>
//	/// <returns>返回元素在list中的位置，如果不存在则返回-1</returns>
//	int LocalElem(const T&);
//
//	T& PriorElem(const T&);
//	T& NextElem(const T&);
//
//	/// <summary>
//	///	优先移动，没有移动则拷贝
//	/// </summary>
//	bool Insert(const int, T&&);
//	bool BackInsert(T&&);
//	bool FrontInsert(T&&);
//
//	/// <summary>
//	///	在链表尾节点处添加一串节点
//	/// </summary>
//	bool Append(LinkedNode*);
//
//	/// <summray>
//	///	对list进行遍历，对所有的元素执行指定操作
//	/// </summary>
//	/// <param name="visitor">对元素指定的操作</param>
//	/// <returns>操作成功与否</returns>
//	bool Traverse();
//
//	/// <summary>
//	///	元素访问
//	/// </summary>
//	T& GetElem(int);
//	T& operator[](int);
//	const T& operator[](int) const;
//
//	/// <summary>
//	///	list union，将另一个LinkedList并入当前LinkedList;
//	/// 被插入的元素应当和原来的list没有关联，移动或者拷贝
//	/// </summary>
//	LinkedList& Union(LinkedList);
//	LinkedList& operator+=(LinkedList);
//
//	/// <summary>
//	///	list Merge, 返回新的LinkedList，两个LinkedList的元素并入新的LinkedList
//	/// 被插入的元素应当和原来的list没有关联，移动或者拷贝
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