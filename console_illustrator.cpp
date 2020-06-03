#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include "console_illustrator.hpp"

using namespace ConsoleIllusrators;

DoubleBufferedTextConsole::DoubleBufferedTextConsole(COORD leftTop, COORD size)
    :  _leftTop(leftTop), _size(size), _firstBuffer(nullptr), _secondBuffer(nullptr)
{
    _consoleHandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    if (_consoleHandle == INVALID_HANDLE_VALUE)
        throw std::runtime_error("invalid console handle value");

    _firstBuffer = new CHAR_INFO[_size.X * _size.Y];
    _secondBuffer = new CHAR_INFO[_size.X * _size.Y];

    memset(_secondBuffer, 0, _size.X*_size.Y*sizeof(CHAR_INFO));
    memcpy(_firstBuffer, _secondBuffer, _size.X*_size.Y*sizeof(CHAR_INFO));
}

DoubleBufferedTextConsole::~DoubleBufferedTextConsole()
{
    delete [] _firstBuffer;
    delete [] _secondBuffer;
}

void DoubleBufferedTextConsole::select()
{
    if (!SetConsoleActiveScreenBuffer(_consoleHandle))
        throw std::runtime_error("error with making console buffer active");

    CONSOLE_CURSOR_INFO cInfo = { 1, FALSE };
    SetConsoleCursorInfo(_consoleHandle, &cInfo);

    SMALL_RECT region;
    region.Left = 0;
    region.Top = 0;
    region.Right = 0;
    region.Bottom = 0;
    if (!SetConsoleWindowInfo(_consoleHandle, TRUE, &region))
        throw std::runtime_error("SetConsoleWindowInfo");

    if (!SetConsoleScreenBufferSize(_consoleHandle, _size))
        throw std::runtime_error("invalid console buffer size");

    region.Left = 0;
    region.Top = 0;
    region.Right = _size.X-1;
    region.Bottom = _size.Y-1;
    if (!SetConsoleWindowInfo(_consoleHandle, TRUE, &region))
        throw std::runtime_error("error with console window coordinates");

    if (!SetWindowPos(GetConsoleWindow(), NULL, _leftTop.X, _leftTop.Y, 1, 1,
                 SWP_NOZORDER | SWP_NOSIZE))
        throw std::runtime_error("SetWindowPos");

    CHAR_INFO instance;
    instance.Char.UnicodeChar = instance.Char.AsciiChar = rand();
    instance.Attributes = rand();
    for (int i = 0; i < _size.X*_size.Y; ++i)
        _secondBuffer[i] = instance;

//    COORD zeroPoint = { 0, 0 };
//    WriteConsoleOutput(_consoleHandle, _firstBuffer, _size, zeroPoint, &region);
}
