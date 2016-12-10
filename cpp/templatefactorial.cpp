#include <iostream>

template <int N>
class fact {
   public:
   enum { val=N*fact<N-1>::val };
};

template<>
class fact<1> {
   public:
   enum {val=1};
};

int main() {
   std::cout << fact<3>::val << std::endl;
   return 0;
}

