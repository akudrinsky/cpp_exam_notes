// Question 1

/*
 size_t - гарантируется, что в него поместится размер в байтах наибольшего возможного объекта в рамках данного устройства (unsigned).
 Лучше unsigned int, unsigned long и т.п. тем, что он независим от устройства (главным образом, разрядности процессора), что обеспечивает лучшую переносимость.
 */

/* О неявном приведении типов (компилятор чаще всего кинет warning, мб с -Wall) */
// problem 1
template<class T>
class Array {
    public:
    Array (int size);
    //...
    int length () const;
};                                      // bad - negative sized arrays?

template<class T>
class Array {
    public:
    Array (unsigned int size);          // size is now unsigned
    // ...
    unsigned int length () const;       // return type is now unsigned
};

                                        // still some problem.
Array<int> a (-1);                      // cast to big value (2^32 - 1)

                                        // want to detect such errors.
                                        // easy way - rewrite initial prototype and add <if> statement

template<class T>
Array<T>::Array (int size) {            // quite safe
#ifdef DEBUG
    if (size < 0) {
        // throw an exception or take some other action;
    }
#endif
    // ...
}

// of course, length also needs to return int in case we do "int n = a.length ();"

// problem 2
struct MyInt {
    operator int () {
        return 100;
    }
    operator double () {
        return 100.5;
    }
};

int main() {
    MyInt x;
    std::cout << x << '\n';             // CE
}

// Question 2
/*
 break в switch
 break в циклах (разумеется, всех)
 continue - переход в самый конец тела цикла
 */
// problem
while (count < 10) {
    if (count == 5)
        continue;                       // after incrementing the counter
    ++count;
}

// Question 3
//
/* Разница между объявлением и определением
 * Определение подмножество объявления.
 * Различие на примерах
*/

// Синтаксис объявления и определения переменных
/* Определение - */ int x = 10;  // - любое объявление переменной - определение


// Функций
/* Объявление  - */  int x (char b);
/* Определение - */  int x (char b) {};

// Классов и структур
/* Объявление  -  */ class x;
/* Определение -  */ сlass x {...};

 // Алиасов для типов (с помощью слова using)
/* Объявление  -  */ using x = std::vector<int>;
