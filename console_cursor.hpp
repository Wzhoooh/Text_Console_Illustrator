#ifndef CONSOLE_CURSOR_HPP_INCLUDED
#define CONSOLE_CURSOR_HPP_INCLUDED

#include "double_buffered_text_console.hpp"

namespace ConsoleIllusrators
{
    class ConsoleCursor
    {
    public:
        ConsoleCursor(COORD leftUp, COORD size);

        void select() noexcept(false);
        bool moveCursor(COORD cursorCoord) noexcept;
        bool put(CHAR_INFO symbol) noexcept;
        void update() noexcept;
        COORD size() const noexcept;

    private:
        DoubleBufferedTextConsole _console;
        COORD _cursor;
    };
}


#endif // CONSOLE_CURSOR_HPP_INCLUDED
