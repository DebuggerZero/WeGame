#include "color.h"
#include<QTime>
#include<QRandomGenerator>

void color::generateRandomNumber(QColor &cr_)
{

    cr_.setRed(QRandomGenerator::global()->generateDouble()*255);

    cr_.setGreen(QRandomGenerator::global()->generateDouble()*255);

    cr_.setBlue(QRandomGenerator::global()->generateDouble()*255);

}
