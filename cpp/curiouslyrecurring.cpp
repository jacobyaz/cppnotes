#include <iostream>

template <class Derived>
class Base {
public:
	static void writeOut() {
		Derived::writeOutImpl();
	}
};

class Derived : public Base<Derived> {
friend class Base<Derived>;
private:
	static void writeOutImpl() { 
		std::cout << "Base static func called\n"; 
	}
};

int main() {
	Base<Derived>::writeOut();
	return 0;
}

