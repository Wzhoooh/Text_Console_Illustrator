#include "console_cursor.hpp"

using namespace ConsoleIllusrators;

ConsoleCursor::ConsoleCursor(COORD leftUp, COORD size):
    _console(leftUp, size), _cursor({0, 0}){}

void ConsoleCursor::select() noexcept(false)
{
    _console.select();
}

bool ConsoleCursor::moveCursor(COORD cursorCoord) noexcept
{
    COORD size = _console.size();
    if (cursorCoord.X < size.X && cursorCoord.Y < size.Y &&
        cursorCoord.X >= 0 && cursorCoord.Y >= 0)
    {
        _cursor = cursorCoord;
        return true;
    }
    else
        return false;
}

bool ConsoleCursor::put(CHAR_INFO symbol) noexcept
{
    if (symbol.Char.AsciiChar != '\n')
        _console.put(_cursor, symbol);

    // moving cursor
    COORD size = _console.size();
    // new str
    if (symbol.Char.AsciiChar == '\n' || _cursor.X == size.X-1)
    {
        _cursor.X = 0;
        _cursor.Y++;
    }
    else
        _cursor.X++;
}
void ConsoleCursor::update() noexcept
{
    _console.update();
}
COORD ConsoleCursor::size() const noexcept
{
    return _console.size();
}
