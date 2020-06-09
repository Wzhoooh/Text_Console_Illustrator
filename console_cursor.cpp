#include "console_cursor.hpp"

using namespace ConsoleIllusrators;

ConsoleCursor::ConsoleCursor(COORD leftUp, COORD size):
    _console(leftUp, size), _cursor({0, 0}){}

void ConsoleCursor::select() noexcept(false)
{
    _console.select();
}

bool ConsoleCursor::changeCursor(COORD cursorCoord) noexcept
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
    _console.put(_cursor, symbol);
}
void ConsoleCursor::update() noexcept
{
    _console.update();
}
