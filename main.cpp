#include <iostream>
#include <chrono>
//#include <ctime>
#include <cstdlib>
#include <conio.h>
#include "double_buffered_text_console.hpp"
#include "console_cursor.hpp"
#include "text_style_console.hpp"

using namespace ConsoleIllusrators;

void testDoubleBufferedTextConsole();
void testConsoleCursor();

int main()
{
    try
    {
        COORD size = {30, 30};
        TextStyleConsole console({0, 0}, size);
        console.style(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
        for (int i = 0; i < 30*30; ++i)
            console.put(" ");

        console.moveCursor({0, 0});
        console.style(BACKGROUND_BLUE | BACKGROUND_INTENSITY);
        console.put("                          ");
        console.put("                          ");
        console.put("Hello, world!\n\n");
        console.style(BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        console.put("uuuu\n");
        console.moveCursor({5, 6});
        console.put("1234\n");
        console.moveCursor({1, 0});
        console.put("Hello, \n\n");
        console.select();
        console.update();
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

void testDoubleBufferedTextConsole()
{
    COORD size = {30, 30};
    DoubleBufferedTextConsole ci_1({0, 0}, {size.X, size.Y});

    CHAR_INFO instance_1;
    instance_1.Char.UnicodeChar = instance_1.Char.AsciiChar = 'a';
    instance_1.Attributes = FOREGROUND_BLUE | BACKGROUND_GREEN
        | FOREGROUND_INTENSITY;

    CHAR_INFO instance_2;
    instance_2.Char.UnicodeChar = instance_2.Char.AsciiChar = ' ';
    instance_2.Attributes = BACKGROUND_RED | BACKGROUND_INTENSITY;

    ci_1.select();
        for (int i = 0; i < size.Y; ++i)
            for (int j = 0; j < size.X; ++j)
                ci_1.put({j, i}, instance_1);

        ci_1.put({5, 0}, instance_2);
        ci_1.put({4, 1}, instance_2);
        ci_1.put({3, 2}, instance_2);
        ci_1.put({2, 3}, instance_2);
        ci_1.put({1, 4}, instance_2);
        ci_1.put({0, 5}, instance_2);

        int sizeArr = size.Y;
        long long timeStr[sizeArr] = {};
        int numOfStrs = 1;

        for (int i = 1; i <= sizeArr; ++i)
        {
DWORD start = GetTickCount();
            for (int j = 0; j < 100; ++j)
                ci_1.testOfWriteStrings(i);

DWORD elapsed = GetTickCount() - start;
            timeStr[i-1] = elapsed;
        }

        for (int i = 0; i < sizeArr; ++i)
            std::cout << i << '\t' << timeStr[i] << '\n';
}

void testConsoleCursor()
{
    COORD size = {30, 30};
    ConsoleCursor ci_2({0, 0}, {size.X, size.Y});

    CHAR_INFO instance_1;
    instance_1.Char.UnicodeChar = instance_1.Char.AsciiChar = 'a';
    instance_1.Attributes = FOREGROUND_BLUE | BACKGROUND_GREEN
        | FOREGROUND_INTENSITY;

    CHAR_INFO instance_2;
    instance_2.Char.UnicodeChar = instance_2.Char.AsciiChar = ' ';
    instance_2.Attributes = BACKGROUND_RED | BACKGROUND_INTENSITY;

    CHAR_INFO enter;
    enter.Char.UnicodeChar = enter.Char.AsciiChar = '\n';
    enter.Attributes = BACKGROUND_GREEN | BACKGROUND_INTENSITY;

    ci_2.put(instance_1);
    ci_2.put(instance_1);
    ci_2.put(instance_2);
    ci_2.put(instance_1);

    for (int i = 0; i < 30; ++i)
    {
        ci_2.put(instance_1);
        ci_2.put(instance_1);
        ci_2.put(instance_1);
        ci_2.put(instance_2);
    }
    ci_2.put(enter);
    ci_2.put(enter);
    ci_2.put(instance_2);
    ci_2.put(instance_1);

    ci_2.select();
    ci_2.update();
}
