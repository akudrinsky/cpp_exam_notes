// Seems, that iostream is better here
// as a simple way to print STL objects
#include <iostream>
#include <stdexcept>
#include "Question10_array.h"

// TODO: write your declarations here
extern int question1_test(int, const char*[]);
extern void question10_test();

int main(int argc, const char* argv[])
{
    try 
    {
        // TODO: call your tests here
        // question1_test(argc, argv);
        question10_test();
    }
    catch (const std::exception& exc)
    {
        std::cerr << "EXCEPTION CAUGHT: " << exc.what() << std::endl;
    }

    return 0;
}
