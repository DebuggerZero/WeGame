#ifndef CHECK_H
#define CHECK_H

#include <QFont>
#include <QColor>

class Check
{
public:
    Check();
    Check(int x, int y, int value);

    static const int WIDTH = 85;
    static const int HEIGHT = 85;

    int x;
    int y;
    int value;

    QColor getColor();

    QFont getFont();
};

#endif // CHECK_H
