#include <iostream>
class A {
	virtual void foo();
};

class B {
};

class C {
	virtual void foo();
	virtual void foo1();
};

int main() {
	std::cout << sizeof(A) << " " << sizeof(B) << " "<< sizeof(C)  << std::endl;
	return 0;
}

