#include "wndmain.h"
#include <QApplication>

#include"wndlogin.h"
#include "wndmain.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WndLogin w;
    w.show();
    return a.exec();
}
