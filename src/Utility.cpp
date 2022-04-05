#include "Utility.hpp"

#include "ncurses.h"

bool is_opposed_direction(Direction dir_1, Direction dir_2)
{
    return ( (dir_1 == Direction::Down && dir_2 == Direction::Up)
            || (dir_1 == Direction::Up && dir_2 == Direction::Down)
            || (dir_1 == Direction::Left && dir_2 == Direction::Right)
            || (dir_1 == Direction::Right && dir_2 == Direction::Left));
}

Settings::Settings(bool boundaries, bool arrows, bool player)
: boundaries(boundaries)
, arrows(arrows)
, player(player)
{
}

Point::Point(): x(-1), y(-1)
{
}

Point::Point(int x, int y) : x(x), y(y)
{
}

bool Point::operator==(const Point& other) const
{
    return x == other.x && y == other.y;
}

size_t PointHashFunction::operator()(const Point& p) const
{
    return ((p.y) << 16) + (p.x);
}

Cell::Cell(Color color, char ch) : p(-1, -1), col(color)
{
    setChar(ch);
}

Cell::Cell(int x, int y, Color color, char ch) : p(x, y), col(color)
{
    setChar(ch);
}

Cell::Cell(const Point& pos, Color color, char ch) : p(pos), col(color)
{
    setChar(ch);
}

void Cell::draw() const
{
    attron(COLOR_PAIR(col));
    mvprintw(p.y, p.x, printableChar);
}

void Cell::setChar(char newChar)
{
    ch = newChar;
    printableChar[0] = ch;
    printableChar[1] = '\0';
}

void Cell::setColor(Color newColor)
{
    col = newColor;
}


Random::Random()
: rd()
, rng(rd())
, rand(0, __INT_MAX__)
{
}

int Random::getRandom()
{
    return rand(rng);
}

int Random::getRandom(int bound)
{
    return getRandom() % bound;
}