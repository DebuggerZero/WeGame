#include "gamemainwindows.h"
#include "ui_gamemainwindows.h"

GameMainWindows::GameMainWindows(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameMainWindows)
{
    ui->setupUi(this);

    this->setFixedSize(400, 500);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle("2048");
    this->setStyleSheet(Utility::getStyleSheet(":/game/assets/2048/main/main.css"));

    _archive.setGameName("2048");
    _archive.readGameStorage();
    _archive.setStartTime(QDateTime::currentDateTime());
    rule.setBestScore(_archive.getBestScore());

    rule.initGame();
}

GameMainWindows::~GameMainWindows()
{
    _archive.setEndTime(QDateTime::currentDateTime());
    _archive.setBestScore(rule.getBestScore());
    _archive.writeGameStorage();
    emit windowsClose();
    this->disconnect();
    delete ui;
}

void GameMainWindows::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);

    QPainter g(this);
    g.setRenderHint(QPainter::SmoothPixmapTransform);

    QPixmap scoreArea = drawScoreArea("得分", rule.getScore());
    g.drawPixmap(30, 26, scoreArea.width(), scoreArea.height(), scoreArea);

    QPixmap bestScoreArea = drawScoreArea("最高得分", rule.getBestScore());
    g.drawPixmap(220, 26, bestScoreArea.width(), bestScoreArea.height(), bestScoreArea);

    QPixmap gameMap = drawGameMap(rule.getChecks());
    g.drawPixmap(30, 142, gameMap.width(), gameMap.height(), gameMap);
}

void GameMainWindows::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up) {
        rule.move(Utility::up);
        update();
    }
    else if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down) {
        rule.move(Utility::down);
        update();
    }
    else if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left) {
        rule.move(Utility::left);
        update();
    }
    else if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right) {
        rule.move(Utility::right);
        update();
    }
    else if (event->key() == Qt::Key_Escape) {
        int result = QMessageBox::question(this, "提示", "是否重新开始游戏...");
        if (result == QMessageBox::Yes) {
            rule.initGame();
        }
    }
    if (rule.gameOver()) {
        int result = QMessageBox::question(this, "提示", "游戏结束...<br>点击 Yes 重新开始...<br>点击 No 返回主界面...");
        if (result == QMessageBox::Yes) {
            rule.initGame();
        }
        else {
            this->close();
        }
    }
}

QPixmap GameMainWindows::drawScoreArea(QString text, int score)
{
    QPixmap pixmap(150, 96);
    pixmap.fill(Qt::transparent);
    QPainter g(&pixmap);
    g.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    g.setPen(Qt::transparent);
    g.setBrush(QBrush(QColor(196, 196, 196, 150)));
    g.drawRoundedRect(QRect(0, 0, 150, 96), 22, 22);

    g.setPen(Qt::black);
    QFont font("微软雅黑", 14, QFont::Thin, false);
    g.setFont(font);
    QRectF rectf1 = Utility::getFontRect(text, 75, 30, font);
    g.drawText(rectf1, Qt::AlignHCenter | Qt::AlignVCenter, text);

    QString score_ = QString::number(score);
    QRectF rectf2 = Utility::getFontRect(score_, 75, 65, font);
    g.drawText(rectf2, Qt::AlignHCenter | Qt::AlignVCenter, score_);

    return pixmap;
}

QPixmap GameMainWindows::drawGameMap(Check checks[])
{
    QPixmap pixmap(Check::WIDTH * 4, Check::HEIGHT * 4);
    pixmap.fill(Qt::transparent);

    QPainter g(&pixmap);
    g.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    g.setPen(Qt::transparent);
    g.setBrush(QBrush(QColor(196, 196, 196, 150)));
    g.drawRoundedRect(QRect(0, 0, pixmap.width(), pixmap.height()), 42.5, 42.5);

    for (int i = 0; i < 16; i++) {
        g.drawPixmap(checks[i].x * Check::WIDTH, checks[i].y * Check::HEIGHT, drawCheck(checks[i]));
    }

    return pixmap;
}

QPixmap GameMainWindows::drawCheck(Check check)
{
    QPixmap pixmap(Check::WIDTH, Check::HEIGHT);
    pixmap.fill(Qt::transparent);
    QPainter g(&pixmap);
    g.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    g.setPen(Qt::transparent);
    g.setBrush(check.getColor());
    g.drawEllipse(QRectF(0, 0, Check::WIDTH, Check::HEIGHT));

    if (check.value != 0) {
        g.setPen(Qt::black);
        QFont font = check.getFont();
        g.setFont(font);
        QString value = QString::number(check.value);
        QRectF rectf1 = Utility::getFontRect(value, Check::WIDTH / 2, Check::HEIGHT / 2, font);
        g.drawText(rectf1, Qt::AlignHCenter | Qt::AlignVCenter, value);
    }

    return pixmap;
}


