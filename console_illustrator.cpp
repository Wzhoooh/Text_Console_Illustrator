#include <stdexcept>
#include <iostream>
#include "console_illustrator.hpp"

ConsoleIllusrator::ConsoleIllusrator(COORD size, int backgroundColor)
    : _size(size), _backgroundColor(backgroundColor)
{
    _consoleHandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    if (_consoleHandle == INVALID_HANDLE_VALUE)
        throw std::runtime_error("invalid console handle value");
    if (!SetConsoleActiveScreenBuffer(_consoleHandle))
        throw std::runtime_error("error with making console buffer active");

    CONSOLE_CURSOR_INFO cInfo = { 1, FALSE };
    SetConsoleCursorInfo(_consoleHandle, &cInfo);
    MoveWindow(GetConsoleWindow(), 0, 0, 0, 0, true);

    if (!SetConsoleScreenBufferSize(_consoleHandle, _size))
        throw std::runtime_error("invalid size");

    SMALL_RECT region;
    region.Left = 0;
    region.Top = 0;
    region.Right = _size.X-1;
    region.Bottom = _size.Y-1;
    if (!SetConsoleWindowInfo(_consoleHandle, true, &region))
        throw std::runtime_error("error with console window coordinates");

    _firstBuffer = new CHAR_INFO[_size.X * _size.Y];
    _secondBuffer = new CHAR_INFO[_size.X * _size.Y];

    CHAR_INFO instance;
    instance.Char.UnicodeChar = instance.Char.AsciiChar = 0;
    instance.Attributes = _backgroundColor;
    for (int i = 0; i < _size.X*_size.Y; ++i)
        _firstBuffer[i] = instance;

    memcpy(_secondBuffer, _firstBuffer, _size.X*_size.Y*sizeof(CHAR_INFO));

    COORD zeroPoint = { 0, 0 };
    WriteConsoleOutput(_consoleHandle, _firstBuffer, _size,
                                   zeroPoint, &region);
}

ConsoleIllusrator::~ConsoleIllusrator()
{
    delete [] _firstBuffer;
    delete [] _secondBuffer;
}
