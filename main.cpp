#include <iostream>
//#include <ctime>
#include <cstdlib>
#include "console_illustrator.hpp"
#include "tests/console_illustrator.hpp"

using namespace ConsoleIllusrators;

int main()
{
    //srand(time(0));
    try
    {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD size = GetLargestConsoleWindowSize(handle);
        DoubleBufferedTextConsole ci_1({50, 50}, {20, 20});
        DoubleBufferedTextConsole ci_2({10, 10}, {40, 40});
        DoubleBufferedTextConsole ci_3({30, 30}, {30, 30});
        for (int i = 0; i < 9; i++)
        {
            ci_1.select();
            //Sleep(50);
            ci_3.select();
            //Sleep(50);
            ci_2.select();
            //Sleep(50);
            ci_3.select();
            //Sleep(50);
        }

        SetConsoleActiveScreenBuffer(handle);
        std::cout << "finish";
    }
    catch(std::exception& e)
    {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleActiveScreenBuffer(handle);
        std::cerr << "FATAL ERROR: " << e.what();
    }
}
