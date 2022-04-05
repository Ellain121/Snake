#ifndef GAME_HPP
#define GAME_HPP

#include "Utility.hpp"
#include "Snake.hpp"

#include <vector>
#include <string>
#include <map>


class Game
{
    public:
                    Game();
                    ~Game();
    
        void        init();
        void        initColors();
        void        initKeys();
        void        buildBoundaries();
        
        void        createFruit();

        void        run();

        void        draw();
        void        update();
        void        handleInput(int input);

        void        drawGameInfo();
    
    private:
        bool                                mGameOver;

        Settings                            mGameSettings;
        int                                 mGameScore;

        std::vector<Point>                  mBoundaries;
        Snake                               mSnake;
        Point                               mFruit;
        std::map<Keyboard, Direction>       mKeyToDirection;

        std::string                         mDebugString;

        Random                              mFruitRandomEngine;

};

#endif