#ifndef WNDLOGIN_H
#define WNDLOGIN_H

#include <QWidget>
#include <QAction>
#include <QFile>
#include <QLineEdit>
#include <QMessageBox>
#include <QDir>
#include <QPalette>
#include "wndmain.h"

namespace Ui {
class WndLogin;
}

class WndLogin : public QWidget
{
    Q_OBJECT

public:
    explicit WndLogin(QWidget *parent = nullptr);
    ~WndLogin();
    void Init();
    bool isTrue();

private:
    bool isFix(const QString str1,const QString str2);
    bool isEmUser(const QString str);
    bool isTre();
private slots:
    void on_btnReg_clicked();

    void on_btnRet_clicked();

    void on_btnReg__clicked();

    void on_btnLogin_clicked();

private:
    Ui::WndLogin *ui;

};

#endif // WNDLOGIN_H
