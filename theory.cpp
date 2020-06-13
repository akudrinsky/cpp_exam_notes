// Question 1
// про виды памяти: https://www.intuit.ru/studies/courses/2193/67/lecture/1976?page=6

void foo () {
    int x = 1;          // автоматическая переменная - время жизни ограничено областью видимости, уничтожается при выходе из функции
}

void foo () {
    static int x = 1;   // статическая - значение сохраняется между вызовами функции
}
//подробнее: https://www.math.spbu.ru/user/nlebedin/theory_static.pdf

// Про выделение памяти и освобождение стоит добавить, но я не знаю что, можно про принцип работы наверное
// Утечки и двойное удаление - есть в min_theory.cpp

// Question 2
// Про дилемму не понял :(
// Ссылки: https://www.tutorialspoint.com/cplusplus/cpp_references.htm, https://habr.com/ru/post/479358/ (весьма жестко, но интересно)
// Висячие ссылки:
int& fun () {
    int a = 0;
    return a;
}

int main () {
    int a = fun ();
    std::cout << a; // в сложном случае, может быть мусор, хотя в этом примере эта возможность очень маловероятна
}
// Продление жизни (если я правильно понял вопрос)
void fun (const int& x) {
    //... использование каких-то манипуляций с x
}
int main () {
    fun (10);   // корректно.
}
/*
 Выдержки из стандарта.
 ⁴ [...] Temporary objects are destroyed as the last step in evaluating the full-expression that (lexically) contains the point where they were created. [...]
 
 ⁵ There are three contexts in which temporaries are destroyed at a different point than the end of the full-expression. [...]
 
 ⁶ The third context is when a reference is bound to a temporary object. The temporary object to which the reference is bound or the temporary object that is the complete object of a subobject to which the reference is bound persists for the lifetime of the reference [...] The exceptions to this lifetime rule are:
 
 (6.9) — A temporary object bound to a reference parameter in a function call persists until the completion of the full-expression containing the call.
 
 (6.10) — The lifetime of a temporary bound to the returned value in a function return statement is not extended; the temporary is destroyed at the end of the full-expression in the return statement.
 */
// Прикольный пример, подтверждающий, что "все работает только на той же инструкции": https://husl.ru/questions/731506

// Question 3
// Правило трех
/*
 Правило трёх (также известное как «Закон Большой Тройки» или «Большая Тройка») — правило в C++, гласящее, что если класс или структура определяет один из следующих методов, то они должны явным образом определить все три метода:
 
 @ Деструктор
 @ Конструктор копирования
 @ Оператор присваивания копированием
 */

// Правило пяти
/*
 Вдобавок к уже названным:
 @ Конструктор перемещения
 @ Оператор присваивания перемещением
 // перемещение - для тех объектов, которые больше не будут нужны (http://simpletechtalks.com/copy-constructor-vs-move-constructor/)
 */

// Initialization list - faster (see "explanation" in https://en.cppreference.com/w/cpp/language/constructor)
// Also an example, where it is necessary
#include <iostream>
using namespace std;

class Test {
    int& t;
public:
    Test (int& t) : t(t) {}  // Initializer list must be used
    int getT () { return t; }
};

int main() {
    int x = 20;
    Test t1 (x);
    cout << t1.getT () << endl;
    x = 30;
    cout << t1.getT () << endl;
    return 0;
}
/* OUTPUT:
 20
 30
 */

// Делегирующие конструкторы - те, что вызывают другие ради избежания copy-past
// https://ravesli.com/urok-119-delegiruyushhie-konstruktory/
