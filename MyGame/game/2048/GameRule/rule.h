#ifndef RULE_H
#define RULE_H

#include "game/Utility/utility.h"
#include "game/2048/check.h"

#include <QVector>
#include <QTime>

class Rule
{
public:
    Rule();

    void initGame();

    int getScore();

    int getBestScore();

    void setBestScore(int bestScore);

    Check* getChecks();

    void move(Utility::Direction direction);

    bool gameOver();

private:
    Check _checks[16];

    int _score;

    int _bestScore;

    void moveUp();

    void moveDown();

    void moveLeft();

    void moveRight();

    QVector<Check*> getEmptyCheck();

    void createCheck();
};

#endif // RULE_H
