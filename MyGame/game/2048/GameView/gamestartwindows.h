#ifndef GAMESTARTWINDOWS_H
#define GAMESTARTWINDOWS_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QStyleOption>
#include <QMessageBox>

#include "game/2048/GameView/gamemainwindows.h"
#include "game/Utility/utility.h"
#include "Archive/archive.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GameStartWindows; }
QT_END_NAMESPACE

class GameStartWindows : public QWidget
{
    Q_OBJECT

public:
    GameStartWindows(QWidget *parent = nullptr);
    ~GameStartWindows();

    void paintEvent(QPaintEvent* event);

signals:
    void windowsClose();

private:
    Ui::GameStartWindows *ui;

    GameMainWindows* gameMainWindows_;
};
#endif // GAMESTARTWINDOWS_H
