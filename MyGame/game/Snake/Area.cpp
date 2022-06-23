#include "Area.h"

Area::Area()
{
    initGame();

    _archive.setGameName("贪吃蛇");
    _archive.readGameStorage();
    snake->bestScore = _archive.getBestScore();
    _archive.setStartTime(QDateTime::currentDateTime());
}

Area::~Area()
{
    _archive.setBestScore(snake->bestScore);
    _archive.setEndTime(QDateTime::currentDateTime());
    _archive.writeGameStorage();
}

void Area::initGame()
{
    gameMap = _utility.CLASSICSMAP;
    snake->initSnake(gameMap);
    food->createFood(gameMap);
    direction = Utility::right;
}

bool Area::gameOver(){
    return !snake->move(gameMap, direction);
}

void Area::createFood()
{
    food->createFood(gameMap);
}

int Area::getScore()
{
    return snake->score;
}

int Area::getBestScore()
{
    return snake->bestScore;
}
