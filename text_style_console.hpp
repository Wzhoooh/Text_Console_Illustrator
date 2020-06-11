#ifndef TEXT_STYLE_CONSOLE_HPP_INCLUDED
#define TEXT_STYLE_CONSOLE_HPP_INCLUDED

#include "console_cursor.hpp"

namespace ConsoleIllusrators
{
    class TextStyleConsole
    {
    public:
        TextStyleConsole(COORD leftUp, COORD size);

        void select() noexcept(false);
        void style(WORD style) noexcept;
        void moveCursor(COORD cursorCoord) noexcept;
        void put(const char*) noexcept;
        void update() noexcept;
        COORD size() const noexcept;

    private:
        ConsoleCursor _console;
        WORD _style;
    };
}

#endif // TEXT_STYLE_CONSOLE_HPP_INCLUDED
