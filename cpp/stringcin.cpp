#include <iostream>
#include <string>

using namespace std;

int main() {

string str = "1";
string result = "";
while (cin >> str) {   
   result += str;
}
cout << result << endl;
return 0;
}
