#include <iostream>
#include <string>

using namespace std; // g++ -std=c++17 *.cpp -o app


int main() {
    string s;
    std::cout << sizeof(s) << std::endl; 

    int i;
    for (i = 0; i < 10000; ++i) {
        s += "FUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCKFUCK";
        s += to_string(i);
    }

    std::cout << sizeof(s) << std::endl; 

    return 0;
}