#include "wndlogin.h"
#include "ui_wndlogin.h"


WndLogin::WndLogin(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::WndLogin)
{
    ui->setupUi(this);

    this->setWindowTitle("MyGame");
    this->setStyleSheet(Utility::getStyleSheet(":/image/wndlogin.qss"));

    Init();
}

WndLogin::~WndLogin()
{
    delete ui;
}

void WndLogin::Init()
{

    QTimer *timer=new QTimer;
    player = new QMediaPlayer;
    videoWidget = new QVideoWidget();
    player->setVideoOutput(videoWidget);
    player->setSource(QUrl("qrc:/image/image/1000.mp4"));
    this->setCentralWidget(videoWidget);
    ui->verticalLayout_2->addWidget(videoWidget);
    //ui->verticalLayout
    //connect(player,&QMediaPlayer::durationChanged,this,&MainWindow::getduration);
    videoWidget->show();
    player->play();
    connect(timer,&QTimer::timeout,this,[=](){
        player->setPosition(0);
    });
    timer->start(179900);

    QAction *searchAction_0 = new QAction(ui->eAccount);
    searchAction_0->setIcon(QIcon(":/image/image/accountIcon.svg"));
    ui->eAccount->addAction(searchAction_0,QLineEdit::LeadingPosition);

    QAction *searchAction_1 = new QAction(ui->ePass);
    searchAction_1->setIcon(QIcon(":/image/image/passwordIcon.svg"));
    ui->ePass->addAction(searchAction_1, QLineEdit::LeadingPosition);

    QAction *searchAction_2 = new QAction(ui->eUers);
    searchAction_2->setIcon(QIcon(":/image/image/unameIcon.svg"));
    ui->eUers->addAction(searchAction_2,QLineEdit::LeadingPosition);

    QAction *searchAction_3 = new QAction(ui->eAccount_);
    searchAction_3->setIcon(QIcon(":/image/image/accountIcon.svg"));
    ui->eAccount_->addAction(searchAction_3,QLineEdit::LeadingPosition);

    QAction *searchAction_4 = new QAction(ui->ePassword);
    searchAction_4->setIcon(QIcon(":/image/image/passwordIcon.svg"));
    ui->ePassword->addAction(searchAction_4,QLineEdit::LeadingPosition);

    QAction *searchAction_5 = new QAction(ui->ePassword_);
    searchAction_5->setIcon(QIcon(":/image/image/passwordIcon.svg"));
    ui->ePassword_->addAction(searchAction_5,QLineEdit::LeadingPosition);

    QPalette wrong_1;
    wrong_1.setColor(QPalette::PlaceholderText,QColor(127,127,127));
    ui->eUers->setPalette(wrong_1);
    ui->eUers->setPlaceholderText(QString("输入用户名："));

    QPalette wrong_2;
    wrong_2.setColor(QPalette::PlaceholderText,QColor(127,127,127));
    ui->ePassword_->setPalette(wrong_2);
    ui->ePassword_->setPlaceholderText(QString("输入密码："));


    QPalette wrong_3;
    wrong_3.setColor(QPalette::PlaceholderText,QColor(127,127,127));
    ui->eAccount_->setPalette(wrong_3);
    ui->eUers->setPlaceholderText(QString("输入账号："));

    QPalette wrong_4;
    wrong_4.setColor(QPalette::PlaceholderText,QColor(127,127,127));
    ui->ePassword_->setPalette(wrong_4);
    ui->ePassword_->setPlaceholderText(QString("确认密码："));
}

bool WndLogin::isTrue()
{
    QString thisaccount= ui->eAccount->text();
    QString thisPass= ui->ePass->text();
    Archive archive;

    if(!archive.isLogin(thisaccount, thisPass)){
        QMessageBox::information(NULL, "登录失败", "用户或密码错误或为空！！"); //警告乱码问题
        return false;
    }
    return true;
}

void WndLogin::on_btnReg_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->sReg);
}

void WndLogin::on_btnRet_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->sLogin);
}

void WndLogin::on_btnReg__clicked()
{
    const QString user = ui->eUers->text();
    const QString account = ui->eAccount_->text();
    const QString onePass= ui->ePassword->text();
    const QString RePass= ui->ePassword_->text();

    Archive archive;

    if (onePass == "" && RePass == "") {
        QMessageBox::information(NULL,"错误","密码不能为空！！"); //警告乱码问题
    }
    else if (onePass != RePass) {
        ui->ePassword_->clear();
        QPalette wrong;
        wrong.setColor(QPalette::PlaceholderText,QColor(255,0,0));
        ui->ePassword_->setPalette(wrong);
        ui->ePassword_->setPlaceholderText(QString("密码输入有误！"));
    }
    else {
        if (archive.isRegister(account, user, onePass)) {
            QMessageBox::information(NULL,"注册成功","欢迎！！");     //警告乱码问题
            ui->stackedWidget->setCurrentWidget(ui->sLogin);

        }
        else {
            QMessageBox::information(NULL,"提示","账号已存在或账号未按照规定格式输入....<br>账号由小于4位数的数字和字母组成...");
        }
    }

    //清除
    ui->eAccount_->clear();
    ui->ePassword->clear();
    ui->ePassword_->clear();
    ui->eUers->clear();
}

void WndLogin::on_btnLogin_clicked()
{
    if(isTrue() && ui->eAccount && ui->ePassword)
    {
        WndMain *a = new WndMain();

        a->show();

        close();
    }
}

