#include "Game.hpp"

#include "ncurses.h"

#include <iostream>
#include <unistd.h>
#include <unordered_set>

constexpr int WIDTH = 80;
constexpr int HEIGHT = 20;
constexpr int SNAKE_MAX_LENGTH = 1000;

#define bound_cell '#'
#define bound_cell_printable "#"
#define fruit_cell_printable "F"

Game::Game()
: mGameOver(false)
, mGameSettings(false, true, true)
, mGameScore(0)
, mBoundaries()
, mSnake(Point(WIDTH / 2, HEIGHT / 2), WIDTH, HEIGHT)
, mFruit(0, 0)
, mDebugString("Debug potato")
, mFruitRandomEngine()
{

    initscr();
    keypad(stdscr, true);
    start_color();
    curs_set(0);
    noecho();
}

Game::~Game()
{
    endwin();
}

void Game::init()
{
    initColors();
    initKeys();
    buildBoundaries();
    createFruit();
}

void Game::createFruit()
{
    std::vector<Point> empty_cells;
    std::unordered_set<Point, PointHashFunction> busy_cells = mSnake.getSnakeCells();

    for (int h = 1; h < HEIGHT - 1; ++h)
    for (int w = 1; w < WIDTH - 1; ++w)
    {
        if (busy_cells.find(Point(w, h)) == busy_cells.end())
        {
            empty_cells.push_back(Point(w, h));
        }
    }

    int fruitINDX = mFruitRandomEngine.getRandom(empty_cells.size());
    mFruit = empty_cells[fruitINDX];
}

void Game::initColors()
{
    init_pair(Color::Red, COLOR_RED, 0);
    init_pair(Color::Green, COLOR_GREEN, 0);
    init_pair(Color::White, COLOR_WHITE, 0);
    init_pair(Color::Magenta, COLOR_MAGENTA, 0);
    init_pair(Color::Cyan, COLOR_CYAN, 0);
    init_pair(Color::Green_White, COLOR_GREEN, COLOR_WHITE);
}

void Game::initKeys()
{
    mKeyToDirection[Keyboard::Down] = Direction::Down;
    mKeyToDirection[Keyboard::Up] = Direction::Up;
    mKeyToDirection[Keyboard::Left] = Direction::Left;
    mKeyToDirection[Keyboard::Right] = Direction::Right;
}

void Game::buildBoundaries()
{
    for (int h = 0; h < HEIGHT; ++h)
    for (int w = 0; w < WIDTH; ++w)
    {
        if (h == 0 || w == 0 || w + 1 == WIDTH || h + 1 == HEIGHT)
        {
            mBoundaries.push_back(Point(w, h));
        }
    }
}

void Game::run()
{
    halfdelay(1.f);
    while (!mGameOver)
    {
        int ch = getch();
        flushinp();
        handleInput(ch);
        update();
        draw();
        usleep(1000);   
    }
}

void Game::update()
{
    bool fruitEaten;
    mGameOver = !mSnake.update(mGameSettings, mFruit, fruitEaten);
    if (fruitEaten)
    {
        mGameScore += 10;
        createFruit();
    }
}

void Game::handleInput(int input)
{
    mDebugString = std::to_string(input);
    if (mKeyToDirection.find((Keyboard)input) != mKeyToDirection.end())
    {
        mSnake.setDirection(mKeyToDirection[(Keyboard)input]);
    }
}

void Game::drawGameInfo()
{
    attron(COLOR_PAIR(Color::White));
    std::string info = "Score: " + std::to_string(mGameScore);
    size_t infoLength = info.size();
    mvprintw(HEIGHT, 0, info.c_str());


    info = "| Snake length: " + std::to_string(mSnake.getSnakeLength());
    mvprintw(HEIGHT, infoLength + 2, info.c_str());

    attron(COLOR_PAIR(Color::Red));
    mDebugString = "Debug: " + mDebugString;
    mvprintw(HEIGHT + 2, 0, mDebugString.c_str());
}

void Game::draw()
{
    clear();
    attron(COLOR_PAIR(1));

    // Draw boundaries
    char st = '#';
    const char* ptr = &st;

    attron(COLOR_PAIR(Color::Magenta));
    for (auto& bound : mBoundaries)
    {
        mvprintw(bound.y, bound.x, bound_cell_printable);
    }

    // draw Fruit
    attron(COLOR_PAIR(Color::White));
    mvprintw(mFruit.y, mFruit.x, fruit_cell_printable);

    // Draw snake
    mSnake.draw();

    drawGameInfo();

    refresh();
}