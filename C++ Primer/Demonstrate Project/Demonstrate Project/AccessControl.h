
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

// 只能访问public成员，protected成员是不可访问的
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

// 都不能访问，public成员变成protected
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

// 所有成员都变成private
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

// 都不可访问
void MotFriendFun(F f){
	
}

class G : public D
{
public:
	void Fun(){
		// publicA 可视，但是不可访问
		//int a = publicA;
		// protectedA不可访问
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