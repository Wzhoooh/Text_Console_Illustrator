#include <iostream>
#include <chrono>
//#include <ctime>
#include <cstdlib>
#include "console_illustrator.hpp"
#include "tests/console_illustrator.hpp"

using namespace ConsoleIllusrators;

int main()
{
    try
    {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD size = GetLargestConsoleWindowSize(handle);
        DoubleBufferedTextConsole ci_1({50, 50}, {20, 20});

        CHAR_INFO instance_1;
        instance_1.Char.UnicodeChar = instance_1.Char.AsciiChar = 'a';
        instance_1.Attributes = FOREGROUND_BLUE | BACKGROUND_GREEN
            | FOREGROUND_INTENSITY;

        CHAR_INFO instance_2;
        instance_2.Char.UnicodeChar = instance_2.Char.AsciiChar = '|';
        instance_2.Attributes = FOREGROUND_RED | BACKGROUND_BLUE
            | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY;

        ci_1.select();
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 10; i++)
            ci_1.modifyCell({i, 3}, instance_1);
        ci_1.update();
        for (int i = 0; i < 5; i++)
            ci_1.modifyCell({8, i}, instance_2);
        ci_1.update();
        for (int i = 0; i < 30; i++)
            ci_1.modifyCell({4, i}, instance_1);
        ci_1.update();

        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        Sleep(5000);

        SetConsoleActiveScreenBuffer(handle);
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        std::cout << "finish: " << microseconds << " mkrS\n";
    }
    catch(std::exception& e)
    {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleActiveScreenBuffer(handle);
        std::cerr << "FATAL ERROR: " << e.what();
    }
}
