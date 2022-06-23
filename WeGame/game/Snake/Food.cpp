#include "Food.h"

Food::Food()
{

}

void Food::createFood(QVector<QVector<int>> &map)
{
    QVector<int*> list = getEmpty(map);
    if(!list.empty()){
        srand(time(NULL));
        int n = rand() % list.size();
        *list[n] = _utility.FOOD_ID;
    }
}

QVector<int*> Food::getEmpty(QVector<QVector<int>> &map){
    QVector<int*> list;
    for (int x = 0; x < map.size(); x++){
        for (int y = 0; y < map[0].size(); y++){
            if (map[x][y] == 0){
                list.push_back(&map[x][y]);
            }
        }
    }
    return list;
}
