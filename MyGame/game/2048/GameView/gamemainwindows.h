#ifndef GAMEMAINWINDOWS_H
#define GAMEMAINWINDOWS_H

#include <QWidget>
#include <QPaintEvent>
#include <QStyleOption>
#include <QPainter>
#include <QPixmap>
#include <QPainterPath>
#include <QFont>
#include <QKeyEvent>
#include <QMessageBox>
#include <QDateTime>

#include "game/2048/GameRule/rule.h"
#include "game/2048/check.h"
#include "archive/archive.h"
#include "game/Utility/utility.h"

namespace Ui {
class GameMainWindows;
}

class GameMainWindows : public QWidget
{
    Q_OBJECT

public:
    explicit GameMainWindows(QWidget *parent = nullptr);
    ~GameMainWindows();

    void paintEvent(QPaintEvent* event) override;

    void keyPressEvent(QKeyEvent* event) override;

signals:
    void windowsClose();

private:
    Ui::GameMainWindows *ui;

    QPixmap drawScoreArea(QString text, int score);

    QPixmap drawGameMap(Check checks[]);

    QPixmap drawCheck(Check check);

    Rule rule;

    Archive _archive;
};

#endif // GAMEMAINWINDOWS_H
