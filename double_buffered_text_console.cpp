#include <stdexcept>
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include "double_buffered_text_console.hpp"

using namespace ConsoleIllusrators;

DoubleBufferedTextConsole::DoubleBufferedTextConsole(COORD leftTop, COORD size)
    :  _leftTop(leftTop), _size(size), _firstBuffer(nullptr), _secondBuffer(nullptr),
    _consoleHandle(CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL))
{
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
    if (_consoleHandle == INVALID_HANDLE_VALUE)
        throw std::runtime_error("invalid console handle value");
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

    WriteConsoleOutput(_consoleHandle, _firstBuffer, _size, { 0, 0 }, &region);
}

bool DoubleBufferedTextConsole::putSymbol(COORD symbCoord, CHAR_INFO symbol)
{
    SHORT index = getIndex(symbCoord);
    if (index >= 0)
    {
        _secondBuffer[index] = symbol;
        return true;
    }
    else return false;
}

SHORT DoubleBufferedTextConsole::getIndex(COORD symbCoord)
{
    if (symbCoord.X < _size.X && symbCoord.Y < _size.Y &&
        symbCoord.X >= 0 && symbCoord.Y >= 0)
        return symbCoord.Y * _size.X + symbCoord.X;
    else return -1;
}

COORD DoubleBufferedTextConsole::getXY(SHORT index)
{
    return { index % _size.X, index / _size.X };
}

void DoubleBufferedTextConsole::update()
{
    for (int i = 0; i < _size.X * _size.Y; ++i)
    {
        ///! have to change, not optimised
        if (_firstBuffer[i].Char.AsciiChar != _secondBuffer[i].Char.AsciiChar ||
            _firstBuffer[i].Char.UnicodeChar != _secondBuffer[i].Char.UnicodeChar ||
            _firstBuffer[i].Attributes != _secondBuffer[i].Attributes)
        {
            SMALL_RECT region;
            region.Left = getXY(i).X;
            region.Top = getXY(i).Y;
            region.Right = getXY(i).X;
            region.Bottom = getXY(i).Y;
            _firstBuffer[i] = _secondBuffer[i];
            WriteConsoleOutput(_consoleHandle, _firstBuffer+i, {1, 1}, {0, 0}, &region);
        }
    }
}

void DoubleBufferedTextConsole::testOfWriteStrings(int numStrings)
{
    SMALL_RECT region;
    for (int i = 0; i < _size.Y; i += numStrings)
    {
        region.Left = 0;
        region.Top = i;
        region.Right = _size.X - 1;
        region.Bottom = i + numStrings - 1;
        WriteConsoleOutput(_consoleHandle, _secondBuffer,
                        {_size.X, _size.Y}, {0, i}, &region);
    }
}


