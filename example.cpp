#include<iostream>
using namespace std;

int& fun () {
    int a = 02;
    return a;
}

int main () {
    int a = fun ();
    std::cout << a;
}
