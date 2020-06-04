#include <iostream>
#include <chrono>
//#include <ctime>
#include <cstdlib>
#include <conio.h>
#include "double_buffered_text_console.hpp"

using namespace ConsoleIllusrators;

auto timeMicroseconds()
{
    return std::chrono::high_resolution_clock::now();
}

int main()
{
    try
    {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD size = GetLargestConsoleWindowSize(handle);
        DoubleBufferedTextConsole ci_1({0, 0}, {size.X, size.Y});

        CHAR_INFO instance_1;
        instance_1.Char.UnicodeChar = instance_1.Char.AsciiChar = 'a';
        instance_1.Attributes = FOREGROUND_BLUE | BACKGROUND_GREEN
            | FOREGROUND_INTENSITY;

        CHAR_INFO instance_2;
        instance_2.Char.UnicodeChar = instance_2.Char.AsciiChar = '|';
        instance_2.Attributes = FOREGROUND_RED | BACKGROUND_BLUE
            | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY;

        ci_1.select();
        for (int i = 0; i < size.Y; ++i)
            for (int j = 0; j < size.X; ++j)
                ci_1.putSymbol({j, i}, instance_1);

        int sizeArr = size.X * size.Y;
        long long time[sizeArr] = {};

        for (int i = 1; i < sizeArr; ++i)
        {
auto start = timeMicroseconds();
            for (int j = 0; j < 1; j++)
                ci_1.testOfWriteConsoleOutput(i);

auto elapsed = timeMicroseconds() - start;
            time[i] = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        }

        SetConsoleActiveScreenBuffer(handle);
        //long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        std::cout << "finish: ";
        for (int i = 1; i < sizeArr; ++i)
            std::cout << "(" << i << ": " << time[i] << ") ";
    }
    catch(std::exception& e)
    {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleActiveScreenBuffer(handle);
        std::cerr << "FATAL ERROR: " << e.what() << "\n";
        std::cerr << "Press any key to continue...";
        getch();
        std::cerr << "\n";
    }
}
