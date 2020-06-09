#ifndef DOUBLE_BUFFERED_TEXT_CONSOLE_HPP_INCLUDED
#define DOUBLE_BUFFERED_TEXT_CONSOLE_HPP_INCLUDED

#define _WIN32_WINNT 0x0500
#include <windows.h>

namespace ConsoleIllusrators
{
    // Strict guarantee of exceptions safety
    class DoubleBufferedTextConsole
    {
    public:
        DoubleBufferedTextConsole(COORD leftTop, COORD size);
        ~DoubleBufferedTextConsole();

        void select() noexcept(false);
        bool put(COORD symbCoord, CHAR_INFO symbol) noexcept;
        CHAR_INFO get(COORD symbCoord) const noexcept(false);
        void update() noexcept;
        COORD size() const noexcept;

        void testOfWriteStrings(int numStrings) noexcept;

    private:
        SHORT getIndex(COORD symbCoord) const noexcept;
        COORD getXY(SHORT index) const noexcept;

    private:
        HANDLE _consoleHandle;
        const COORD _size;
        const COORD _leftTop;
        CHAR_INFO* _firstBuffer;
        CHAR_INFO* _secondBuffer;
    };

}

#endif // DOUBLE_BUFFERED_TEXT_CONSOLE_HPP_INCLUDED
