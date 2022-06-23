#include "rule.h"

Rule::Rule()
{
    initGame();
}

void Rule::initGame()
{
    for (int i = 0; i < 4 * 4; i++) {
        _checks[i] = Check(i % 4, i / 4, 0);
    }
    _score = 0;
    createCheck();
}

int Rule::getScore()
{
    return _score;
}

int Rule::getBestScore()
{
    return _bestScore;
}

void Rule::setBestScore(int bestScore)
{
    _bestScore = bestScore;
}

Check *Rule::getChecks()
{
    return _checks;
}

void Rule::move(Utility::Direction direction)
{
    switch (direction){
        case Utility::up:
            moveUp();
            break;
        case Utility::down:
            moveDown();
            break;
        case Utility::left:
            moveLeft();
            break;
        case Utility::right:
            moveRight();
            break;
    }
    if (_bestScore < _score) {
        _bestScore = _score;
    }
    createCheck();
}

bool Rule::gameOver()
{
    QVector<Check*> list = getEmptyCheck();
    if (list.empty()) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (_checks[i + j * 4].value == _checks[i + (j + 1) * 4].value ||
                        _checks[i * 4 + j].value == _checks[i * 4 + j + 1].value) {
                    return false;
                }
            }
        }
        for (int i = 12; i < 15; i++) {
            if (_checks[i].value == _checks[i + 1].value) {
                return false;
            }
        }
        for (int i = 3; i < 15; i += 4) {
            if (_checks[i].value == _checks[i + 4].value) {
                return false;
            }
        }
    }
    return list.empty();
}

void Rule::moveUp()
{
    for (int x = 0; x < 4; x++) {
        for (int y = 1, index = 0; y < 4; y++) {
            if (_checks[x + y * 4].value > 0) {
                if (_checks[x + y * 4].value == _checks[x + index * 4].value){
                    _checks[x + y * 4].value = 0;
                    _checks[x + index * 4].value <<= 1;
                    _score += _checks[x + index * 4].value;
                }
                else if (_checks[x + index * 4].value == 0 || _checks[x + (++index) * 4].value == 0) {
                    _checks[x + index * 4].value = _checks[x + y * 4].value;
                    _checks[x + y * 4].value = 0;
                }
            }
        }
    }
}

void Rule::moveDown()
{
    for (int x = 3; x >= 0; x--) {
        for (int y = 2, index = 3; y >= 0; y--) {
            if (_checks[x + y * 4].value > 0) {
                if (_checks[x + y * 4].value == _checks[x + index * 4].value){
                    _checks[x + y * 4].value = 0;
                    _checks[x + index * 4].value <<= 1;
                    _score += _checks[x + index * 4].value;
                }
                else if (_checks[x + index * 4].value == 0 || _checks[x + (--index) * 4].value == 0) {
                    _checks[x + index * 4].value = _checks[x + y * 4].value;
                    _checks[x + y * 4].value = 0;
                }
            }
        }
    }
}

void Rule::moveLeft()
{
    for (int x = 0; x < 4; x++) {
        for (int y = 1, index = 0; y < 4; y++) {
            if (_checks[x * 4 + y].value > 0) {
                if (_checks[x * 4 + y].value == _checks[index + x * 4].value){
                    _checks[x * 4 + y].value = 0;
                    _checks[x * 4 + index].value <<= 1;
                    _score += _checks[x * 4 + index].value;
                }
                else if (_checks[index + x * 4].value == 0 || _checks[(++index) + x * 4].value == 0) {
                    _checks[x * 4 + index].value = _checks[x * 4 + y].value;
                    _checks[x * 4 + y].value = 0;
                }
            }
        }
    }
}

void Rule::moveRight()
{
    for (int x = 3; x >= 0; x--) {
        for (int y = 2, index = 3; y >= 0; y--) {
            if (_checks[x * 4 + y].value > 0) {
                if (_checks[x * 4 + y].value == _checks[index + x * 4].value){
                    _checks[x * 4 + y].value = 0;
                    _checks[x * 4 + index].value <<= 1;
                    _score += _checks[x * 4 + index].value;
                }
                else if (_checks[index + x * 4].value == 0 || _checks[(--index) + x * 4].value == 0) {
                    _checks[x * 4 + index].value = _checks[x * 4 + y].value;
                    _checks[x * 4 + y].value = 0;
                }
            }
        }
    }
}

QVector<Check*> Rule::getEmptyCheck()
{
    QVector<Check*> list;
    for (int i = 0; i < 16; i++) {
        if (_checks[i].value == 0) {
            list.push_back(&_checks[i]);
        }
    }
    return list;
}

void Rule::createCheck()
{
    QVector<Check*> list = getEmptyCheck();
    if (!list.empty()) {
        srand(time(NULL));
        int index = rand() % (list.length());
        list[index]->value = (rand() % 4 % 4 != 0) ? 2 : 4;
    }
}
