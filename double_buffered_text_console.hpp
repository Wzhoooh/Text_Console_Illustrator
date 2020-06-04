#ifndef DOUBLE_BUFFERED_TEXT_CONSOLE_HPP_INCLUDED
#define DOUBLE_BUFFERED_TEXT_CONSOLE_HPP_INCLUDED

#include <cstddef>
#define _WIN32_WINNT 0x0500
#include <windows.h>

namespace ConsoleIllusrators
{
    class DoubleBufferedTextConsole
    {
    public:
        DoubleBufferedTextConsole(COORD leftUp, COORD size);
        ~DoubleBufferedTextConsole();

        void select();
        bool putSymbol(COORD symbCoord, CHAR_INFO symbol);
        void update();

        void testOfWriteConsoleOutput(int numCells);

    private:
        SHORT getIndex(COORD symbCoord);
        COORD getXY(SHORT index);

    private:
        const HANDLE _consoleHandle;
        const COORD _size;
        const COORD _leftTop;
        CHAR_INFO* _firstBuffer;
        CHAR_INFO* _secondBuffer;
    };

}

#endif // DOUBLE_BUFFERED_TEXT_CONSOLE_HPP_INCLUDED
