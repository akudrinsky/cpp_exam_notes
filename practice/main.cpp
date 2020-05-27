// Seems, that iostream is better here
// as a simple way to print STL objects
#include <iostream>
#include <stdexcept>

// TODO: write your declarations here
extern int question1_test(int, const char*[]);

int main(int argc, const char* argv[])
{
    try 
    {
        // TODO: call your tests here
        question1_test(argc, argv);
    }
    catch (const std::exception& exc)
    {
        std::cerr << "EXCEPTION CAUGHT: " << exc.what() << std::endl;
    }

    return 0;
}
