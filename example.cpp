#include <cstdio>
#include <iostream>

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
}
