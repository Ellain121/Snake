#include "Snake.hpp"

#include "ncurses.h"

Snake::Snake(const Point& startPos, const int wBound, const int hBound)
: mHead(startPos, Color::Green, '0')
, WIDTH_BOUND(wBound)
, HEIGHT_BOUND(hBound)
, mTail()
, mDir(Direction::None)
{
    mTail.push_back(Cell(mHead.p.x + 1, mHead.p.y, Color::Cyan, 'o'));
}

void Snake::setDirection(Direction dir)
{
    if (!is_opposed_direction(mDir, dir))
        mDir = dir;
}

bool Snake::update(const Settings& gameSettings, const Point& fruitPos, bool& fruitEaten)
{
    if (mDir == Direction::None) return true;
    int x = mHead.p.x + dirDiff[(int)mDir];
    int y = mHead.p.y + dirDiff[(int)mDir + 1];
    bool boundaryCollision = (x <= 0 || y <= 0 || x >= WIDTH_BOUND - 1 || y >= HEIGHT_BOUND - 1);
    if (boundaryCollision)
    {
        if (gameSettings.boundaries)
        {
            return false;
        }
        else
        {
            if (x <= 0) x = WIDTH_BOUND - 2;
            if (x >= WIDTH_BOUND - 1) x = 1;
            if (y <= 0) y = HEIGHT_BOUND - 2;
            if (y >= HEIGHT_BOUND - 1) y = 1;
        }
    }


    Point upperPos = mHead.p;
    mHead.p.x = x;
    mHead.p.y = y;
    fruitEaten = mHead.p == fruitPos;
    if (fruitEaten)
    {
        mTail.push_back(Cell(Color::Cyan, 'o'));
    }

    for (int i = mTail.size() - 1; i >= 1; i--)
    {
        mTail[i].p = mTail[i-1].p;
    }
    mTail[0].p = upperPos;

    // Tail collision
    for (auto& tail : mTail)
    {
        if (mHead.p == tail.p)
        return false;
    }

    return true;
}   

void Snake::draw() const
{
    mHead.draw();
    for (auto& tailCell : mTail)
        tailCell.draw();
}

std::unordered_set<Point, PointHashFunction> Snake::getSnakeCells() const
{
    std::unordered_set<Point, PointHashFunction> snake_cells;
    snake_cells.insert(mHead.p);
    for (auto& tail : mTail)
    {
        snake_cells.insert(tail.p);
    }

    return snake_cells;
}

size_t Snake::getSnakeLength() const
{
    return mTail.size() + 1;
}