#include "wndlogin.h"
#include "ui_wndlogin.h"

WndLogin::WndLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WndLogin)
{
    ui->setupUi(this);

    this->setStyleSheet(Utility::getStyleSheet(":/image/wndlogin.qss"));
}

WndLogin::~WndLogin()
{
    delete ui;
}

void WndLogin::Init()
{
    QAction *searchAction_0 = new QAction(ui->eAccount);
    searchAction_0->setIcon(QIcon(":/image/image/accountIcon.png"));
    ui->eAccount->addAction(searchAction_0,QLineEdit::LeadingPosition);

    QAction *searchAction_1 = new QAction(ui->ePass);
    searchAction_1->setIcon(QIcon(":/image/image/passwordIcon.png"));
    ui->ePass->addAction(searchAction_1,QLineEdit::LeadingPosition);

    QAction *searchAction_2 = new QAction(ui->eUers);
    searchAction_2->setIcon(QIcon(":/image/image/unameIcon.png"));
    ui->eUers->addAction(searchAction_2,QLineEdit::LeadingPosition);

    QAction *searchAction_3 = new QAction(ui->eAccount_);
    searchAction_3->setIcon(QIcon(":/image/image/accountIcon.png"));
    ui->eAccount_->addAction(searchAction_3,QLineEdit::LeadingPosition);

    QAction *searchAction_4 = new QAction(ui->ePassword);
    searchAction_4->setIcon(QIcon(":/image/image/passwordIcon.png"));
    ui->ePassword->addAction(searchAction_4,QLineEdit::LeadingPosition);

    QAction *searchAction_5 = new QAction(ui->ePassword_);
    searchAction_5->setIcon(QIcon(":/image/image/passwordIcon.png"));
    ui->ePassword_->addAction(searchAction_5,QLineEdit::LeadingPosition);

    //密码模式
    ui->ePass->setEchoMode(QLineEdit::Password);
    ui->ePassword->setEchoMode(QLineEdit::Password);
    ui->ePassword_->setEchoMode(QLineEdit::Password);

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
{    QString thisaccount= ui->eAccount->text();
     QString thisPass=ui->ePass->text();

     if(thisPass==nullptr||thisaccount==nullptr){
         QMessageBox::information(NULL, "登录失败", "用户或密码不能为空！！"); //警告乱码问题
         return false;
     }

     QFile file("C:/MyGame/user/" + thisaccount+ "/" +thisaccount + ".txt");

     file.open(QIODevice::ReadOnly);

     QByteArray data=file.readAll();
     const QString TrulyPass = QString(data);
     file.close();

     if(thisPass==TrulyPass) return true;
     else{
         QMessageBox::information(NULL,"登录失败","用户或密码错误！！"); //警告乱码问题
         return false;
    }
}

bool WndLogin::isFix(const QString str1, const QString str2)
{
    //确定两次输入的密码是否相同

    if(str1==nullptr&&str2==nullptr)
    {
        QDir UserDir("C:/MyGame/user/"+ui->eAccount_->text());

        UserDir.removeRecursively();

        QMessageBox::information(NULL,"错误","密码不能为空！！"); //警告乱码问题
        return false;
    }
    else if(!(str1==str2)){
        //不同
        ui->ePassword_->clear();
        QPalette wrong;
        wrong.setColor(QPalette::PlaceholderText,QColor(255,0,0));
        ui->ePassword_->setPalette(wrong);
        ui->ePassword_->setPlaceholderText(QString("密码输入有误！"));

        QDir UserDir("C:/MyGame/user/"+ui->eAccount_->text());
        //创建文件夹
        UserDir.removeRecursively();
        return  false;
    }

    //相同及正确
    QPalette wrong;
    wrong.setColor(QPalette::PlaceholderText,QColor(127,127,127));
    ui->ePassword_->setPalette(wrong);
    ui->ePassword_->setPlaceholderText(QString("确认密码："));
    return  true;
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
    //判断用户名是否存在
    if(!isEmUser(ui->eAccount_->text())) return;
    //判断长度
    if(!isTre()) return;
    //接收密码字符串
    const QString onePass=ui->ePassword->text();
    const QString RePass=ui->ePassword_->text();

    //调用IsFix函数判断 密码不一致
    if(!isFix(onePass,RePass)) return ;

    QDir UserDir("C:/MyGame/user/"+ui->eAccount_->text()+"/");

    QFile UserFile(UserDir.filePath(ui->eAccount_->text()+".txt"));

    //打开文件
    UserFile.open(QIODevice::WriteOnly);

    //创建新用户，并存到本地文档中储存
     UserFile.write(onePass.toLatin1());
     QMessageBox::information(NULL,"注册成功","欢迎！！");     //警告乱码问题
     UserFile.close();

     //清除
     ui->eAccount_->clear();
     ui->ePassword->clear();
     ui->ePassword_->clear();
     ui->eUers->clear();
}

bool WndLogin::isEmUser(const QString str)
{
    if(str==nullptr){
        QMessageBox::information(NULL,"错误","账号不能为空！");     //警告乱码问题
        return false;
    }
    QDir Findir("C:/MyGame/user/"+str);
    //查找用户名是否相同
    if(Findir.exists()){ //找到
        //创建用户失败
        ui->eAccount_->clear();
         QPalette wrong;
         wrong.setColor(QPalette::PlaceholderText,QColor(255,0,0));
         ui->eAccount_->setPalette(wrong);
         ui->eAccount_->setPlaceholderText(QString("此账号已存在"));
         return false;
       }

    QDir UserDir1("C:/MyGame/user/");
    //创建文件夹
    UserDir1.mkpath(str);

    QPalette wrong;
    wrong.setColor(QPalette::PlaceholderText,QColor(127,127,127));
    ui->eAccount_->setPalette(wrong);
    ui->eAccount_->setPlaceholderText(QString("四位数字或字母"));
    return  true;
}

bool WndLogin::isTre()
{
    if(!(ui->eAccount_->text().length()<5&&ui->ePassword->text().length()<10))
    {
       QMessageBox::information(NULL,"错误","用户名或密码违法长度！");     //警告乱码问题
       ui->eAccount_->clear();
       ui->ePassword->clear();
       ui->ePassword_->clear();
       ui->eUers->clear();
       QDir UserDir("C:/MyGame/user/"+ui->eAccount_->text());

       UserDir.removeRecursively();

       return false;
    }
    return true;
}



void WndLogin::on_btnLogin_clicked()
{
    if(isTrue()&&ui->eAccount&&ui->ePassword)
    {
        WndMain *a=new WndMain();

        QFile qss(":/image/wndmain.qss");
        qss.open(QFile::ReadOnly);
        qApp->setStyleSheet(qss.readAll());
        qss.close();

        a->show();

        close();
    }
}

