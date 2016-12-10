#include <iostream>
#include <vector>

void sortBinaryArray(std::vector<int> & v) {
	if (v.empty()) return;
	int i=-1;
	int j = v.size();
	while (i<j) {
		while (!v[++i]) {}
		while (v[--j]) {}
		if (i<j) {
			v[i]=0;
			v[j]=1;
		}
	}
}

void printVector(std::vector<int> & v) {
	for (auto iter=v.begin(); iter != v.end(); ++iter) {
		std::cout << *iter << ",";
	}
	std::cout << std::endl;
}

int main(void){
	std::vector<int> A={1,1,0,0,1};
	printVector(A);
	sortBinaryArray(A);
	printVector(A);
	
	std::cout << std::endl;
	
	std::vector<int> B={0,0,0,0,0};
	printVector(B);
	sortBinaryArray(B);
	printVector(B);
	
	std::cout << std::endl;
	
	std::vector<int> C={};
	printVector(C);
	sortBinaryArray(C);
	printVector(C);

	return 0;
}

