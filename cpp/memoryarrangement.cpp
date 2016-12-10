#include <iostream>

class base {
public:
   base() : a(2),c(3) {}
   int a;
   int c;
   int getA() { return a; }
};

class derived : public base {
public:
   derived() : b(7) {}
   int b;
   int getB() { return b; }
};

void disp(base * p, int n) {
	for (int i=0;i<n;++i) 
      std::cout << (p+i)->getA() << std::endl;
}

int main() {
   base b[3];
   disp(b,3);
   derived d[3];
   disp(d,3);
}

