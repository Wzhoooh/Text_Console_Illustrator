#ifndef CONSOLE_ILLUSTRATOR_HPP_INCLUDED
#define CONSOLE_ILLUSTRATOR_HPP_INCLUDED

#include <cstddef>
#define _WIN32_WINNT 0x0500
#include <windows.h>

class ConsoleIllusrator
{
public:
    ConsoleIllusrator(COORD size, int backgroundColor);
    ~ConsoleIllusrator();

    bool editCell(COORD, CHAR_INFO);
    bool editCell(COORD, CHAR_INFO, int backgroundColor);
    void update();

private:
    HANDLE _consoleHandle;
    int _backgroundColor;
    COORD _size;
    CHAR_INFO* _firstBuffer;
    CHAR_INFO* _secondBuffer;
};

#endif // CONSOLE_ILLUSTRATOR_HPP_INCLUDED
