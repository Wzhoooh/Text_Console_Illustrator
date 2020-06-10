#include "text_style_console.hpp"

using namespace ConsoleIllusrators;

TextStyleConsole::TextStyleConsole(COORD leftUp, COORD size):
    _console(leftUp, size), _style(0){}

void TextStyleConsole::select() noexcept(false)
{
    _console.select();
}
void TextStyleConsole::style(WORD style) noexcept
{
    _style = style;
}
void TextStyleConsole::put(const char* str) noexcept
{
    int len = strlen(str);
    CHAR_INFO instance;
    instance.Attributes = _style;

    for (int i = 0; i < len; i++)
    {
        instance.Char.AsciiChar = str[i];
        _console.put(instance);
    }
}
void TextStyleConsole::update() noexcept
{
    _console.update();
}
COORD TextStyleConsole::size() const noexcept
{
    return _console.size();
}
