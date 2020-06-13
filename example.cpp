#include <map>
#include <vector>
#include <iostream>

int main() {
    std::map<int, int> a;
    a[2] = 3;
    a[5] = 7;
    a[10] = 2;
    
    for (auto it = a.begin (); it != a.end (); ++it)
        std::cout << it->second << '\n';
    
    for (auto it : a)
        std::cout << it.first << '\n';
    
    
    std::vector<int> b;
    b.push_back (2);
    b.push_back (3);
    b.push_back (7);
    
    for (auto it = b.begin (); it < b.end (); ++it)
        std::cout << *it << '\n';
    
    for (auto it : b)
        std::cout << it << '\n';
    
    return 0;
}
