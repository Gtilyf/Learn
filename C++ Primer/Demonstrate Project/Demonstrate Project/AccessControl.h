
class A
{
public:
	int publicA;
private:
	int privateA;
protected:
	int protectedA;
};

class B : public A
{

	friend void Fun(B b);

public:
	void Fun(){
		int a = publicA;
		a = protectedA;
	}
private:

};

// ֻ�ܷ���public��Ա��protected��Ա�ǲ��ɷ��ʵ�
void NotFriendFun(B b){
	int a = b.publicA;
}

class C : protected A
{

	friend void Fun(C c);

public:
	void Fun(){
		int a = publicA;
		a = protectedA;
	}

private:

};

// �����ܷ��ʣ�public��Ա���protected
void NotFriendFun(C c){

}

class D : private A
{

	friend void Fun(D d);

public:
	void Fun(){
		int a = publicA;
		a = protectedA;
	}
private:

};

// ���г�Ա�����private
void NotFriendFun(D d){

}

class E : public B
{
public:
	void Fun(){
		int a = publicA;
		a = protectedA;
	}
};

void NotFriendFun(E e){
	int a = e.publicA;
}

class F : public C
{
public:
	void Fun(){
		int a = publicA;
		a = protectedA;
	}
};

// �����ɷ���
void MotFriendFun(F f){
	
}

class G : public D
{
public:
	void Fun(){
		// publicA ���ӣ����ǲ��ɷ���
		//int a = publicA;
		// protectedA���ɷ���
	}
private:
};

void Fun(B b){
	int a = b.publicA;
	a = b.protectedA;
}

void Fun(C c){
	int a = c.protectedA;
	a = c.publicA;
}

void Fun(D d){
	d.protectedA;
	d.publicA;
}