#include <iostream>

template <class Policy>
class Base : private Policy {
using Policy::writeOut;
public:
	void write() { writeOut(); }
};

class EnglishPolicy {
protected:
	void writeOut() { std::cout << "English\n"; }
};

class GermanPolicy {
protected:
	void writeOut() { std::cout << "German\n"; }
};

int main() {
	Base<EnglishPolicy> E;
	Base<GermanPolicy> G;
	
	E.write();
	G.write();
	
	return 0;
}

