#include "piece.h"

Piece::Piece()
{
}

Piece::Piece(int x, int y, int value)
{
    this->x = x;
    this->y = y;
    this->value = value;
}

void Piece::initPiece()
{
    for (int i = 0; i < chessboard.size(); i++){
        for (int j = 0; j < chessboard[0].size(); j++){
            chessboard[i][j] = 2;
        }
    }
    pieces.clear();
}

QVector<QVector<int> > Piece::getChessboard()
{
    return this->chessboard;
}

QVector<Piece> Piece::getPieces()
{
    return this->pieces;
}

void Piece::playChess(int x, int y, int step)
{
    pieces.push_back(Piece(x, y, step % 2));
    chessboard[x][y] = step % 2;
}

void Piece::undo()
{
    if (!pieces.empty()){
        int undoX = pieces[pieces.size() - 1].x;
        int undoY = pieces[pieces.size() - 1].y;
        chessboard[undoX][undoY] = 2;
        pieces.remove(pieces.size() - 1);
    }
}

int Piece::gameOver(int x, int y)
{
    if (pieces.size() == chessboard.size() * chessboard[0].size()){
        return 3;
    }

    int across = left(x, y) + right(x, y) + 1;
    int vertical = up(x, y) + down(x, y) + 1;
    int leftRhombic = leftUp(x, y) + rightDown(x, y) + 1;
    int rightRhombic = leftDown(x, y) + rightUp(x, y) + 1;

    if (across >= 5 || vertical >= 5 || leftRhombic >= 5 || rightRhombic >= 5){
        return  chessboard[x][y];
    }

    return 2;
}

int Piece::left(int x, int y)
{
    int number = 0;
    while (x - 1 >= 0 && chessboard[x][y] == chessboard[x - 1][y]){
        number++;
        x--;
    }
    return number;
}

int Piece::right(int x, int y)
{
    int number = 0;
    while (x + 1 < chessboard.size() && chessboard[x][y] == chessboard[x + 1][y]){
        number++;
        x++;
    }
    return number;
}

int Piece::up(int x, int y)
{
    int number = 0;
    while (y - 1 >= 0 && chessboard[x][y] == chessboard[x][y - 1]){
        number++;
        y--;
    }
    return number;
}

int Piece::down(int x, int y)
{
    int number = 0;
    while (y + 1 < chessboard.size() && chessboard[x][y] == chessboard[x][y + 1]){
        number++;
        y++;
    }
    return number;
}

int Piece::rightUp(int x, int y)
{
    int number = 0;
    while (x + 1 < chessboard[0].size() && y - 1 >= 0 && chessboard[x][y] == chessboard[x + 1][y - 1]){
        number++;
        x++;
        y--;
    }
    return number;
}

int Piece::leftDown(int x, int y)
{
    int number = 0;
    while (x - 1 >= 0 && y + 1 < chessboard.size() && chessboard[x][y] == chessboard[x - 1][y + 1]){
        number++;
        x--;
        y++;
    }
    return number;
}

int Piece::leftUp(int x, int y)
{
    int number = 0;
    while (x - 1 >= 0 && y - 1 >= 0 && chessboard[x][y] == chessboard[x - 1][y - 1]){
        number++;
        x--;
        y--;
    }
    return number;
}

int Piece::rightDown(int x, int y)
{
    int number = 0;
    while (x + 1 < chessboard[0].size() && y + 1 < chessboard.size() && chessboard[x][y] == chessboard[x + 1][y + 1]){
        number++;
        x++;
        y++;
    }
    return number;
}
