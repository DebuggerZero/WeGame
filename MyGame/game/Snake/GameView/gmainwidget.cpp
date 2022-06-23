#include "gmainwidget.h"
#include "ui_gmainwidget.h"

GMainWidget::GMainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GMainWidget)
{
    ui->setupUi(this);

    this->setWindowTitle("贪吃蛇");
    this->setFixedSize(QSize(805, 556));
    this->setAttribute(Qt::WA_DeleteOnClose);

    area = new Area();
    init();

    _timer = new QTimer(this);
    connect(_timer, &QTimer::timeout, this, [=](){
        update();
    });
    _timer->start(50);

    _backGround.load(":/game/assets/Snake/backGround.png");
}

GMainWidget::~GMainWidget()
{
    emit closeWindows();
    _timer->stop();
    delete area;
    delete _timer;
    delete ui;
}

void GMainWidget::paintEvent(QPaintEvent *)
{
    QPainter g(this);
    g.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing | QPainter::TextAntialiasing);
    g.drawPixmap(0, 0, _backGround);

    int width = 750;
    int height = 450;
    int mapX = (this->width() - width) / 2;
    int mapY = (this->height() - height) / 2;
    g.drawPixmap(mapX, mapY, createMap(width, height));

    QFont font("微软雅黑", 15, QFont::Thin, false);
    g.setFont(font);
    g.setPen(QColor(0, 0, 0, 150));
    QFontMetrics fontMetrics(font);
    QString message = "score: " + QString::number(area->getScore(), 10) +
            " | best: " + QString::number(area->getBestScore(), 10);
    int scoreWidth = fontMetrics.horizontalAdvance(message);
    int scoreHeight = fontMetrics.height();
    int messageX =  (this->width() - scoreWidth) / 2;
    int messageY = (this->height() - scoreHeight) / 5 * 4 + 90;

    QRectF rect(messageX, messageY, scoreWidth, scoreHeight);
    g.drawText(rect, Qt::AlignHCenter | Qt::AlignVCenter, message);
}

void GMainWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W && area->direction != Utility::down){
        area->direction = Utility::up;
    }
    else if (event->key() == Qt::Key_S && area->direction != Utility::up){
        area->direction = Utility::down;
    }
    else if (event->key() == Qt::Key_A && area->direction != Utility::right){
        area->direction = Utility::left;
    }
    else if (event->key() == Qt::Key_D && area->direction != Utility::left){
        area->direction = Utility::right;
    }
}

QPixmap GMainWidget::createMap(int width, int height)
{
    QPixmap pixMap(width, height);
    pixMap.fill(Qt::transparent);
    QPainter g(&pixMap);
    g.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    _speed = 200 * (1.0 - area->getScore() / 100.0);
    if (_speed < 50){
        _speed = 50;
    }
    if (_moveStartTime.msecsTo(QDateTime::currentDateTime()) >= _speed) {
        if (area->gameOver()){
            int result = QMessageBox::question(this, "提示", "游戏结束..<br>点击 Yes 重新开始...<br>点击 No 返回主页...");
            if (result == QMessageBox::Yes){
                init();
            }
            else {
                this->close();
            }
        }
        _moveStartTime = QDateTime::currentDateTime();
    }

    if (_foodStartTime.msecsTo(QDateTime::currentDateTime()) >= 1500){
        area->createFood();
        _foodStartTime = QDateTime::currentDateTime();
    }

    for (int i = 0; i < area->gameMap.size(); i++){
        for (int j = 0; j < area->gameMap[0].size(); j++){
            int id = area->gameMap[i][j];
            if (id == _utility.WALL_ID){
                g.fillRect(i * Area::WIDTH, j * Area::HEIGHT, Area::WIDTH, Area::HEIGHT, QBrush(QColor(155, 155, 155, 100)));
            }
            else if (id == _utility.SNAKE_BODY_ID || id == _utility.SNAKE_HEAD_ID){
                QPainterPath path;
                int x = i * Area::WIDTH;
                int y = j * Area::HEIGHT;
                path.addEllipse(x, y, Area::WIDTH, Area::WIDTH);
                g.fillPath(path, QBrush(QColor((_utility.SNAKE_HEAD_ID - id) * 50, (_utility.SNAKE_HEAD_ID - id) * 50, (_utility.SNAKE_HEAD_ID - id) * 50, 50 * (id + 1))));
            }
            else if (id == _utility.FOOD_ID){
                QPainterPath path;
                int x = i * Area::WIDTH + (Area::WIDTH - Food::WIDTH) / 2;
                int y = j * Area::HEIGHT + (Area::HEIGHT - Food::HEIGHT) / 2;
                path.addEllipse(x, y, Food::WIDTH, Food::HEIGHT);
                g.fillPath(path, QBrush(QColor(200, 200, 200, 150)));
            }
        }
    }

    return pixMap;
}

void GMainWidget::init()
{
    area->initGame();
    _speed = 200;
    _moveStartTime = QDateTime::currentDateTime();
    _foodStartTime = QDateTime::currentDateTime();
}
