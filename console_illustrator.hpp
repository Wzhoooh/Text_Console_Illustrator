#ifndef CONSOLE_ILLUSTRATOR_HPP_INCLUDED
#define CONSOLE_ILLUSTRATOR_HPP_INCLUDED

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
        bool modifyCell(COORD symbCoord, CHAR_INFO symbol);
        void update();

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

#endif // CONSOLE_ILLUSTRATOR_HPP_INCLUDED
