QT       += core gui
QT       += multimedia
QT       += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    archive/archive.cpp \
    game/2048/GameRule/rule.cpp \
    game/2048/GameView/gamemainwindows.cpp \
    game/2048/GameView/gamestartwindows.cpp \
    game/2048/check.cpp \
    game/Color/color.cpp \
    game/Color/widget.cpp \
    game/Gobang/GameView/gmainwindow.cpp \
    game/Gobang/GameView/gstartwindow.cpp \
    game/Gobang/piece.cpp \
    game/Snake/Area.cpp \
    game/Snake/Food.cpp \
    game/Snake/GameView/gmainwidget.cpp \
    game/Snake/GameView/gstartwidght.cpp \
    game/Snake/Snake.cpp \
    game/Utility/utility.cpp \
    main.cpp \
    wndlogin.cpp \
    wndmain.cpp

HEADERS += \
    archive/archive.h \
    game/2048/GameRule/rule.h \
    game/2048/GameView/gamemainwindows.h \
    game/2048/GameView/gamestartwindows.h \
    game/2048/check.h \
    game/Color/color.h \
    game/Color/widget.h \
    game/Gobang/GameView/gmainwindow.h \
    game/Gobang/GameView/gstartwindow.h \
    game/Gobang/piece.h \
    game/Snake/Area.h \
    game/Snake/Food.h \
    game/Snake/GameView/gmainwidget.h \
    game/Snake/GameView/gstartwidght.h \
    game/Snake/Snake.h \
    game/Utility/utility.h \
    wndlogin.h \
    wndmain.h

FORMS += \
    game/2048/GameView/gamemainwindows.ui \
    game/2048/GameView/gamestartwindows.ui \
    game/Color/widget.ui \
    game/Gobang/GameView/gmainwindow.ui \
    game/Gobang/GameView/gstartwindow.ui \
    game/Snake/GameView/gmainwidget.ui \
    game/Snake/GameView/gstartwidght.ui \
    wndlogin.ui \
    wndmain.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    imandqss.qrc
