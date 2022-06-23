#include "Snake.h"

#include <QDebug>

Snake::Snake()
{
}

Snake::Snake(int x, int y){
    this->x = x;
    this->y = y;
}

bool Snake::move(QVector<QVector<int>> &map, Utility::Direction direction){
    int preX = body[body.size() - 1]->x;
    int preY = body[body.size() - 1]->y;
    map[preX][preY] = _utility.BLANK_ID;

    if (direction == Utility::up){
        body[body.size() - 1]->x = head->x;
        body[body.size() - 1]->y = head->y - 1;
    }
    else if (direction == Utility::down){
        body[body.size() - 1]->x = head->x;
        body[body.size() - 1]->y = head->y + 1;
    }
    else if (direction == Utility::right){
        body[body.size() - 1]->x = head->x + 1;
        body[body.size() - 1]->y = head->y;
    }
    else if (direction == Utility::left){
        body[body.size() - 1]->x = head->x - 1;
        body[body.size() - 1]->y = head->y;
    }

    body.push_front(body[body.size() - 1]);
    body.pop_back();

    if (!crash(map)){
        map[body[0]->x][body[0]->y] = _utility.SNAKE_HEAD_ID; //将新头部的 ID 在地图中显示
        map[head->x][head->y] = _utility.SNAKE_BODY_ID; //将原头部转化为身体
        head = body[0]; //将头部指针指向新头部
        return true;
    }

    return false;
}

void Snake::add(){
    int preX = body[body.size() - 1]->x;
    int preY = body[body.size() - 1]->y;

    score++;
    if (score > bestScore) bestScore = score;

    body.push_back(new Snake(preX, preY));
}

void Snake::initSnake(QVector<QVector<int>> &map){

    this->body.clear();
    this->body.push_back(new Snake(3, 1));
    this->body.push_back(new Snake(2, 1));
    this->body.push_back(new Snake(1, 1));
    this->head = this->body[0];
    map[body[0]->x][body[0]->y] = _utility.SNAKE_HEAD_ID;
    map[body[1]->x][body[1]->y] = _utility.SNAKE_BODY_ID;
    map[body[2]->x][body[2]->y] = _utility.SNAKE_BODY_ID;

    score = 0;
}

bool Snake::crash(QVector<QVector<int>> map){
    int id = map[body[0]->x][body[0]->y];
    if (id == _utility.BLANK_ID){
        return false;
    }
    else if (id == _utility.FOOD_ID) {
        add();
        return false;
    }
    return true;
}
