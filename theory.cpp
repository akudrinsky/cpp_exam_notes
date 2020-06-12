// Question 1
// про виды памяти: https://www.intuit.ru/studies/courses/2193/67/lecture/1976?page=6

void foo () {
    int x = 1;          // автоматическая переменная - время жизни ограничено областью видимости, уничтожается при выходе из функции
}

void foo () {
    static int x = 1;   // статическая - значение сохраняется между вызовами функции
}
//подробнее: https://www.math.spbu.ru/user/nlebedin/theory_static.pdf

// динамическая - производится системный вызов с запросом на выделение определённого объема памяти
//                операционной системой
void foo () {

    #include <vector>
    // способы выделения и освобождения динамической памяти:
    
    /* один объект */
    auto vec = new std::vector<int>(10, 0); // выделение памяти под вектор из 10 элементов и его инициализация
                                            // возвращается указатель на выделенный в пямяти объект
    delete vec;

    /* массив объектов */
    auto matrix = new std::vector<int>[10]; // массив из 10-ти пустых векторов. Дополнительно выделяется память
    delete[] matrix;                        // под количество объектов в массиве, чтобы оператор
                                            // delete[] вызвал деструктор для каждого объекта в массиве

    /* выделение определённого количества байт */
    char* data1 = new char[100500];
    delete[] data1;
    // или
    char* data2 = reinterpret_cast<char*>(::operator new(100500));
    ::operator delete(data2);
    // или
    char* data3 = reinterpret_cast<char*>(calloc(100500, sizeof(char))); // бывает полезно, если нужна память,
                                                                        // заполненная нулями (только под linux)
    free(data3);
}
// Основные проблемы: Утечки и двойное удаление - есть в min_theory.cpp

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
