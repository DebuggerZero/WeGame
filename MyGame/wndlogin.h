#ifndef WNDLOGIN_H
#define WNDLOGIN_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMainWindow>
#include <QAction>
#include <QFile>
#include <QLineEdit>
#include <QMessageBox>
#include <QUrl>
#include <QDir>
#include <QPalette>
#include <QTimer>
#include "wndmain.h"

namespace Ui {
class WndLogin;
}

class WndLogin : public QMainWindow
{
    Q_OBJECT

public:
    explicit WndLogin(QMainWindow *parent = nullptr);
    ~WndLogin();
    void Init();
    bool isTrue();

private slots:
    void on_btnReg_clicked();

    void on_btnRet_clicked();

    void on_btnReg__clicked();

    void on_btnLogin_clicked();

private:
    Ui::WndLogin        *_ui;
    QMediaPlayer        *_player;
    QVideoWidget        *_videoWidget;
    QTimer              *_timer;
};

#endif // WNDLOGIN_H
