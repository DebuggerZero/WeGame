#ifndef SNACK_H
#define SNACK_H

#include <QVector>

#include "game/Utility/utility.h"

class Snake
{
public:
    Snake();
    Snake(int x, int y);

    int score;

    int bestScore;

    bool move(QVector<QVector<int>> &map, Utility::Direction direction);

    void initSnake(QVector<QVector<int>> &map);

    bool crash(QVector<QVector<int>> map);

private:

    int x;
    int y;

    QVector<Snake*> body;

    Utility _utility;

    Snake* head;

    void add();
};

#endif // SNACK_H
