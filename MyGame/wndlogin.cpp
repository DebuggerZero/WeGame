#include "wndlogin.h"
#include "ui_wndlogin.h"

WndLogin::WndLogin(QMainWindow *parent) :
    QMainWindow(parent),
    _ui(new Ui::WndLogin)
{
    _ui->setupUi(this);

    this->setWindowTitle("MyGame");
    this->setStyleSheet(Utility::getStyleSheet(":/image/wndlogin.qss"));

    Init();
}

WndLogin::~WndLogin()
{
    delete _ui;
}

void WndLogin::Init()
{
    QTimer *timer = new QTimer;
    _player = new QMediaPlayer;
    _videoWidget = new QVideoWidget();
    _player->setVideoOutput(_videoWidget);
    _player->setSource(QUrl("qrc:/image/image/1000.mp4"));
    this->setCentralWidget(_videoWidget);
    _ui->verticalLayout_2->addWidget(_videoWidget);
    _videoWidget->show();
    _player->play();
    connect(timer,&QTimer::timeout,this,[=](){
        _player->setPosition(0);
    });
    timer->start(179900);

    QAction *searchAction_0 = new QAction(_ui->eAccount);
    searchAction_0->setIcon(QIcon(":/image/image/accountIcon.svg"));
    _ui->eAccount->addAction(searchAction_0,QLineEdit::LeadingPosition);

    QAction *searchAction_1 = new QAction(_ui->ePass);
    searchAction_1->setIcon(QIcon(":/image/image/passwordIcon.svg"));
    _ui->ePass->addAction(searchAction_1, QLineEdit::LeadingPosition);

    QAction *searchAction_2 = new QAction(_ui->eUers);
    searchAction_2->setIcon(QIcon(":/image/image/unameIcon.svg"));
    _ui->eUers->addAction(searchAction_2,QLineEdit::LeadingPosition);

    QAction *searchAction_3 = new QAction(_ui->eAccount_);
    searchAction_3->setIcon(QIcon(":/image/image/accountIcon.svg"));
    _ui->eAccount_->addAction(searchAction_3,QLineEdit::LeadingPosition);

    QAction *searchAction_4 = new QAction(_ui->ePassword);
    searchAction_4->setIcon(QIcon(":/image/image/passwordIcon.svg"));
    _ui->ePassword->addAction(searchAction_4,QLineEdit::LeadingPosition);

    QAction *searchAction_5 = new QAction(_ui->ePassword_);
    searchAction_5->setIcon(QIcon(":/image/image/passwordIcon.svg"));
    _ui->ePassword_->addAction(searchAction_5,QLineEdit::LeadingPosition);

    QPalette wrong_1;
    wrong_1.setColor(QPalette::PlaceholderText,QColor(127,127,127));
    _ui->eUers->setPalette(wrong_1);
    _ui->eUers->setPlaceholderText(QString("输入用户名"));

    QPalette wrong_2;
    wrong_2.setColor(QPalette::PlaceholderText,QColor(127,127,127));
    _ui->ePassword_->setPalette(wrong_2);
    _ui->ePassword_->setPlaceholderText(QString("输入密码"));


    QPalette wrong_3;
    wrong_3.setColor(QPalette::PlaceholderText,QColor(127,127,127));
    _ui->eAccount_->setPalette(wrong_3);
    _ui->eUers->setPlaceholderText(QString("输入账号"));

    QPalette wrong_4;
    wrong_4.setColor(QPalette::PlaceholderText,QColor(127,127,127));
    _ui->ePassword_->setPalette(wrong_4);
    _ui->ePassword_->setPlaceholderText(QString("确认密码"));
}

bool WndLogin::isTrue()
{
    QString thisaccount= _ui->eAccount->text();
    QString thisPass= _ui->ePass->text();
    Archive archive;

    if(!archive.isLogin(thisaccount, thisPass)){
        QMessageBox::information(NULL, "登录失败", "用户或密码错误或为空！！"); //警告乱码问题
        return false;
    }
    return true;
}

void WndLogin::on_btnReg_clicked()
{
    _ui->stackedWidget->setCurrentWidget(_ui->sReg);
}

void WndLogin::on_btnRet_clicked()
{
    _ui->stackedWidget->setCurrentWidget(_ui->sLogin);
}

void WndLogin::on_btnReg__clicked()
{
    const QString user = _ui->eUers->text();
    const QString account = _ui->eAccount_->text();
    const QString onePass= _ui->ePassword->text();
    const QString RePass= _ui->ePassword_->text();

    Archive archive;

    if (onePass == "" && RePass == "") {
        QMessageBox::information(NULL,"错误","密码不能为空！！"); //警告乱码问题
    }
    else if (onePass != RePass) {
        _ui->ePassword_->clear();
        QPalette wrong;
        wrong.setColor(QPalette::PlaceholderText,QColor(255,0,0));
        _ui->ePassword_->setPalette(wrong);
        _ui->ePassword_->setPlaceholderText(QString("密码输入有误！"));
    }
    else {
        QRegularExpression re("^[a-zA-Z0-9_-]+@ [a-zA-Z0-9_-]+ (. [a-zA-Z0-9_-]+)+$");
        QRegularExpressionMatch match = re.match(account);
        bool hasMatch = match.hasMatch();
        QRegularExpressionMatch match_ = re.match(onePass);
        bool hasMatch_ = match_.hasMatch();
        if (archive.isRegister(account, user, onePass)&&hasMatch&&hasMatch_) {
            QMessageBox::information(NULL,"注册成功","欢迎！！");     //警告乱码问题
            _ui->stackedWidget->setCurrentWidget(_ui->sLogin);
        }
        else {
            QMessageBox::information(NULL,"提示","账号已存在或账号未按照规定格式输入....<br>账号由小于4位数的数字和字母组成...");
        }
    }

    //清除
    _ui->eAccount_->clear();
    _ui->ePassword->clear();
    _ui->ePassword_->clear();
    _ui->eUers->clear();
}

void WndLogin::on_btnLogin_clicked()
{
    if(isTrue() && _ui->eAccount && _ui->ePassword)
    {
        WndMain *a = new WndMain();

        a->show();

        close();
    }
}

