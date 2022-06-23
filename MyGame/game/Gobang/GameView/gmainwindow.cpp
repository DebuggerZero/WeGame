#include "gmainwindow.h"
#include "ui_gmainwindow.h"

GMainWindow::GMainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GMainWindow)
{
    ui->setupUi(this);

    _frame.load(":/game/assets/Gobang/main/frame.png");
    _rim.load(":/game/assets/Gobang/main/rim.png");

    this->setFixedSize(QSize(800, 600));
    this->setWindowTitle("五子棋");
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setMouseTracking(true);

    _archive.setGameName("五子棋");
    _archive.readGameStorage();
    _archive.setStartTime(QDateTime::currentDateTime());

    _messageList = new QListWidget(this);
    _messageList->setFocus();
    _messageList->setGeometry(MSGLIST_X, MSGLIST_Y, MSGLIST_WIDTH, MSGLIST_HEIGHT);
    _messageList->setStyleSheet("background-color:transparent");

    initWindow();

    connect(ui->restart, &QPushButton::clicked, this, [=](){
        initWindow();
    });

    connect(ui->undo, &QPushButton::clicked, this, [=](){
        if (_step != 0){
            _piece.undo();
            _step--;
            QString message;
            message = _step % 2 == 0 ? "黑方" : "白方";
            _messageList->addItem(message + "以悔棋");
            _messageList->addItem(message + "重新落棋");
            _messageList->setCurrentRow(_messageList->count() - 1);
        }
    });

    connect(ui->giveUp, &QPushButton::clicked, this, [=](){
        QString message;
        message = _step % 2 == 0 ? "黑方" : "白方";
        int result = QMessageBox::question(this, "提示", message + "是否决定认输...");
        if (result == QMessageBox::Yes){
            int result1 = QMessageBox::question(this, "提示", message + "认输,游戏结束...");
            if (result1 == QMessageBox::Yes || result1 == QMessageBox::No){
                initWindow();
            }
        }
    });

    connect(ui->returnHome, &QPushButton::clicked, this, [=](){
        this->close();
    });

    _timer = new QTimer(this);

    connect(_timer, &QTimer::timeout, this, [=](){
        update();
    });

    _timer->start(10);
}

GMainWindow::~GMainWindow()
{

    _archive.setEndTime(QDateTime::currentDateTime());
    _archive.writeGameStorage();

    emit windowClose();
    _timer->stop();
    delete _timer;
    delete _messageList;
    delete ui;
}

void GMainWindow::paintEvent(QPaintEvent *)
{
    QPainter g(this);
    g.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing | QPainter::TextAntialiasing);

    g.drawPixmap(0, 0, QPixmap(":/game/assets/Gobang/main/backGround.png"));

    g.fillRect(QRectF(0, 0, this->width(), this->height()), QBrush(QColor(255, 255, 200, 100)));

    //======================================================================
    //绘制游戏数据记录区域
    g.setPen(QPen(Qt::black, 3));
    g.drawRect(QRectF(MSGLIST_X - 10, 0, 160, 330));

    QFont font("微软雅黑", 12, QFont::Thin, false);
    g.setFont(font);
    QString stepMsg =  "步数：" + QString::number(_step);
    QRectF rectf = Utility::getFontRect(stepMsg, STEPMSG_X, STEPMSG_Y, font);
    g.drawText(rectf, Qt::AlignHCenter | Qt::AlignVCenter, stepMsg);

    QPainterPath path1;
    path1.addEllipse(QRectF(MSGLIST_X + 20, MSGLIST_Y + MSGLIST_HEIGHT + 45, 30, 30));
    g.fillPath(path1, QBrush(Qt::black));

    QFont font1("微软雅黑", 8, QFont::Thin, false);
    g.setFont(font1);
    QRectF black = Utility::getFontRect("黑方", 665, 300, font1);
    g.drawText(black, Qt::AlignHCenter | Qt::AlignVCenter, "黑方");

    QPainterPath path2;
    path2.addEllipse(QRectF(MSGLIST_X + MSGLIST_WIDTH - 50, MSGLIST_Y + MSGLIST_HEIGHT + 45, 30, 30));
    g.fillPath(path2, QBrush(Qt::white));

    QFont font2("微软雅黑", 8, QFont::Thin, false);
    g.setFont(font1);
    QRectF white = Utility::getFontRect("白方", 735, 300, font2);
    g.drawText(white, Qt::AlignHCenter | Qt::AlignVCenter, "白方");

    int rimX, rimY;
    rimX = _step % 2 == 0 ? MSGLIST_X + 15 : MSGLIST_X + MSGLIST_WIDTH - 55;
    rimY = MSGLIST_Y + MSGLIST_HEIGHT + 40;
    g.drawPixmap(rimX, rimY, _rim);
    //======================================================================

    QPixmap map = drawGameMap(_mouseX / 40, _mouseY / 40);
    g.drawPixmap(0, 0, map);
}

void GMainWindow::mouseMoveEvent(QMouseEvent *event)
{
    _mouseX = event->pos().x();
    _mouseY = event->pos().y();
}

void GMainWindow::mousePressEvent(QMouseEvent *event)
{
    int x = _mouseX / 40;
    int y = _mouseY / 40;
    if (event->button() == Qt::LeftButton) {
        if (x >= 0 && x <= 14 && y >= 0 && y <= 14){
            if ( _piece.getChessboard().at(x).at(y) == 2){
                _piece.playChess(x, y, _step);

                QString message;
                message = _step % 2 == 0 ? "黑方" : "白方";
                QString msg1 = message + "落棋[" + QString::number(x) + ", " + QString::number(y) + "]";
                message = message == "黑方" ? "白方" : "黑方";
                QString msg2 = message + "准备落棋";
                _messageList->addItem(msg1);
                _messageList->addItem(msg2);

                _messageList->setCurrentRow(_messageList->count() - 1);

                this->_step++;//步数 +1
            }

            int gameOver = _piece.gameOver(x, y);
            if (gameOver == 0 || gameOver == 1){
                QString message = gameOver == 0 ? "黑方" : "白方";
                message += "获胜, 游戏结束..";
                _messageList->addItem(message);

                int result = QMessageBox::question(this, "提示", message);
                if (result == QMessageBox::Yes || result == QMessageBox::No){
                    initWindow();
                }
            }
            else if (gameOver == 3){
                int result = QMessageBox::question(this, "提示", "游戏平局...");
                if (result == QMessageBox::Yes || result == QMessageBox::No){
                    initWindow();
                }
            }
        }
    }
}

void GMainWindow::initWindow()
{
    _messageList->clear();
    _messageList->addItem("游戏开始...");
    _messageList->addItem("黑方落棋");
    _piece.initPiece();
    _step = 0;
}

QPixmap GMainWindow::drawGameMap(int x, int y)
{
    QPixmap map(GAMEMAP_WIDTH, GAMEMAP_HEIGHT);
    map.fill(Qt::transparent);

    QPainter g(&map);

    g.setRenderHint(QPainter::Antialiasing);

    //==========================================================
    //绘制棋盘
    g.setPen(QPen(Qt::black, 3));
    g.drawRect(0, 0, 600, 600);

    g.setPen(QPen(Qt::black, 2));
    for (int i = 0; i < 15; i++){
        g.drawLine(20, 20 + i * 40, 580, 20 + i * 40);
        g.drawLine(20 + i * 40, 20, 20 + i * 40, 580);
    }

    QPainterPath path;
    path.addEllipse(295, 295, 10, 10);
    path.addEllipse(135, 135, 10, 10);
    path.addEllipse(135, 455, 10, 10);
    path.addEllipse(455, 135, 10, 10);
    path.addEllipse(455, 455, 10, 10);
    g.fillPath(path, QBrush(QColor(0, 0, 0)));

    if(x >= 0 && x <= 14 && y >= 0 && y <= 14 && _piece.getChessboard().at(x).at(y) == 2){
        int frameX = x * 40 + 5;
        int frameY = y * 40 + 5;
        g.drawPixmap(frameX, frameY, _frame);
    }
    //=============================================================
    //绘制棋子
    QVector<Piece> pieces = _piece.getPieces();
    for (int i = 0; i < pieces.size(); i++){
        QPainterPath path;
        path.addEllipse(pieces[i].x * 40 + 5, pieces[i].y * 40 + 5, 30, 30);
        g.fillPath(path, QBrush(QColor(255 * pieces[i].value, 255 * pieces[i].value, 255 * pieces[i].value)));
    }
    //为新下的棋子添加红框
    if (!pieces.empty()){
        g.drawPixmap(pieces[pieces.size() - 1].x * 40, pieces[pieces.size() - 1].y * 40, _rim);
    }
    //=============================================================

    return map;
}
