#include <iostream>

int main() {
	volatile int const a = 3;	
	//int const a = 3;
	unsigned long int p = (unsigned long int)(&a);
	int * q = (int *)(p);
	*q=*q+1;
	std::cout << a << std::endl;
	// if "a" is defined not volatile, output:3
	// if "a" is defined volatile,  output:4
	// due to compiler optimization
}

