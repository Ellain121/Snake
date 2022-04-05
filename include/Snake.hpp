#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "Utility.hpp"

#include <vector>
#include <unordered_set>

class Snake
{
    public:
                Snake(const Point& startPos, const int wBound, const int hBound);

        void    setDirection(Direction dir);

        bool    update(const Settings& gameSettings, const Point& fruitPos, bool& fruitEaten);
        void    draw() const;
    
        const Point&                                    getPosition() const;
        std::unordered_set<Point, PointHashFunction>    getSnakeCells() const;
        size_t                                          getSnakeLength() const;

    
    private:
        const int               HEIGHT_BOUND;
        const int               WIDTH_BOUND;
        Cell                    mHead;
        std::vector<Cell>       mTail;    
        Direction               mDir;

        int                     dirDiff[5] = {0, -1, 0, 1, 0};       
};

#endif