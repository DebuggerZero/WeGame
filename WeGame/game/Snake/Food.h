#ifndef FOOD_H
#define FOOD_H

#include <QVector>
#include <ctime>

#include "game/Utility/utility.h"

class Food
{
public:
    Food();

    static const int WIDTH = 20;
    static const int HEIGHT = 20;

    void createFood(QVector<QVector<int>> &map);

private:
    Utility _utility;

    QVector<int*> getEmpty(QVector<QVector<int>> &map);
};

#endif // FOOD_H
