#include <iostream>
#include "console_illustrator.hpp"
#include "tests/console_illustrator.hpp"

int main()
{
    try
    {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD size = GetLargestConsoleWindowSize(handle);
        ConsoleIllusrator ci(size, BACKGROUND_RED);
    }
    catch(std::exception& e)
    {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleActiveScreenBuffer(handle);
        std::cerr << "FATAL ERROR: " << e.what();
    }
}
