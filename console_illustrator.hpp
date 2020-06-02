#ifndef CONSOLE_ILLUSTRATOR_HPP_INCLUDED
#define CONSOLE_ILLUSTRATOR_HPP_INCLUDED

struct HANDLE;
struct CHARINFO;

class ConsoleIllusrator
{
public:
    ConsoleIllusrator() = delete;
    ConsoleIllusrator(const ConsoleIllusrator&) = delete;
    ConsoleIllusrator(ConsoleIllusrator&&);
    operator =(const ConsoleIllusrator&) = delete;
    operator =(ConsoleIllusrator&&);
    ConsoleIllusrator(HANDLE, int background); // with console handle

    ~ConsoleIllusrator();

    bool editCell(CHARINFO); // with no background color
    bool editCell(CHARINFO, int); // with background color
    void update();
};

#endif // CONSOLE_ILLUSTRATOR_HPP_INCLUDED
