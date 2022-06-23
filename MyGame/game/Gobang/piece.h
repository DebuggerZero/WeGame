#ifndef PIECE_H
#define PIECE_H

#include <QColor>
#include <QVector>

class Piece
{
public:
    Piece();
    Piece(int x, int y, int value);

    int x;
    int y;
    int value;

    void initPiece();

    QVector<QVector<int>> getChessboard();

    QVector<Piece> getPieces();

    int getStep();

    void playChess(int x, int y, int step);

    void undo();

    int gameOver(int x, int y);

private:
    QVector<QVector<int>> chessboard = QVector<QVector<int>>(15, QVector<int>(15));
    QVector<Piece> pieces;

    int left(int x, int y);
    int right(int x, int y);

    int up(int x, int y);
    int down(int x, int y);

    int rightUp(int x, int y);
    int leftDown(int x, int y);

    int leftUp(int x, int y);
    int rightDown(int x, int y);
};

#endif // PIECE_H
