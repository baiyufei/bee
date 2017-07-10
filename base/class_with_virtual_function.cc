#include <iostream>
class A {
	virtual void foo();
};

class B {
};

int main() {
	std::cout << sizeof(A) << " " << sizeof(B)  << std::endl;
	return 0;
}

