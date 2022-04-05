#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "ncurses.h"

#include <random>

enum class Direction
{
    Up = 0,
    Left,
    Down,
    Right,
    None
};

enum Color
{
    Red = 1,
    Green,
    White,
    Magenta,
    Cyan,
    Green_White,
};

enum class Keyboard
{
    Left = KEY_LEFT,
    Right = KEY_RIGHT,
    Up = KEY_UP,
    Down = KEY_DOWN
};

bool is_opposed_direction(Direction dir_1, Direction dir_2);

struct Settings
{
    Settings(bool boundaries, bool arrows, bool player);

    bool    boundaries;
    bool    arrows;
    bool    player;
};

struct Random
{
    std::random_device rd;
    std::mt19937 rng;
    std::uniform_int_distribution<std::mt19937::result_type> rand;

    Random();
    int getRandom();
    int getRandom(int bound);
};

struct Point
{
    Point();
    Point(int x, int y);
    int x;
    int y;

    bool operator==(const Point& other) const;
};

struct PointHashFunction
{
    size_t operator()(const Point& p) const;
};

struct Cell
{
    public:
        Cell(Color color = Color::White, char ch = ' ');
        Cell(int x, int y, Color color = Color::White, char ch = ' ');
        Cell(const Point& pos, Color color = Color::White, char ch = ' ');

        void    setColor(Color newColor);
        void    setChar(char newChar);

        void    draw() const;

        Point   p;
        Color   col;
        char    ch;

    private:
        char printableChar[2];
};

#endif