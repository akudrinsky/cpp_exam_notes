#include <cstdio>
#include <iostream>
#include <span>

class MyInt {
public:
    int number = 1;
private:
    int a = 2;
};

int main() {
    MyInt i = 0;
    do {
        std::cout << i << '\n';
    }
    while (i < 5);
    std::span<int> a;
}
