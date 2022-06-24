#include "archive.h"

QString Archive::account = "";
QString Archive::userName = "";

Archive::Archive() {

}

Archive::Archive(QString gameName)
{
    _gameName = gameName;
    readGameRecords();
}

Archive::~Archive()
{

}

QString Archive::getGameName()
{
    return _gameName;
}

void Archive::setGameName(QString name)
{
    _gameName = name;
}

void Archive::setStartTime(QDateTime startTime)
{
    _startTime = startTime;
}

void Archive::setEndTime(QDateTime endTime)
{
    _endTime = endTime;
    _gameTime += _startTime.msecsTo(_endTime);
    _number++;
}

int Archive::getBestScore()
{
    return _bestScore;
}

void Archive::setBestScore(int bestScore)
{
    _bestScore = bestScore;
}

int Archive::getNumber()
{
    return _number;
}

long Archive::getGameTime()
{
    return _gameTime;
}

void Archive::writeGameStorage()
{
    QString fullPath = PATH + "Game/" + _gameName;
    createDir("Game/" + _gameName + "/");
    QFile file(fullPath + "/data.txt");
    file.open(QIODevice::WriteOnly);
    QTextStream textStream(&file);
    textStream.setEncoding(QStringConverter::Utf8);

    textStream << "name:" << _gameName << Qt::endl;
    textStream << "bestScore:" << QString::number(_bestScore) << Qt::endl;
    textStream << "number:" << QString::number(_number) << Qt::endl;
    textStream << "gameTime:" << QString::number(_gameTime) << Qt::endl;

    file.close();

    _time.push_back({_number,
                     _bestScore,
                     _startTime.toString("HH:mm:ss"),
                     _endTime.toString("HH:mm:ss")
                    });
    writeGameRecords();
}

void Archive::writeGameRecords()
{
    QString fullPath = PATH + "Game/" + _gameName;
    createDir("Game/" + _gameName + "/");
    QFile file(fullPath + "/records.txt");
    file.open(QIODevice::Append);
    QTextStream textStream(&file);
    textStream.setEncoding(QStringConverter::Utf8);

    textStream << QString::number(_time.at(_time.length() - 1).number) << " " <<
                  QString::number(_time.at(_time.length() - 1).bestScore) << " " <<
                  _time.at(_time.length() - 1).startTime << " " <<
                  _time.at(_time.length() - 1).endTime << Qt::endl;

    file.close();
}

void Archive::readGameStorage()
{
    QString fullPath = PATH + "Game/" + _gameName;
    createDir("Game/" + _gameName + "/");
    QFile file(fullPath + "/data.txt");
    if (!file.exists()) {
        _bestScore = 0;
        _number = 0;
        _gameTime = 0;
        file.close();
        return;
    }
    file.open(QIODevice::ReadOnly);
    QTextStream textStream(&file);
    textStream.setEncoding(QStringConverter::Utf8);

    while (!textStream.atEnd()) {
        QString str = textStream.readLine();
        QStringList list = str.split(":");
        if (list[0] == "name")
            _gameName = list[1];
        else if (list[0] == "bestScore")
            _bestScore = list[1].toInt();
        else if (list[0] == "number")
            _number = list[1].toInt();
        else if (list[0] == "gameTime")
            _gameTime = list[1].toLong();
    }

    file.close();
}

void Archive::readGameRecords()
{
    QString fullPath = PATH + "Game/" + _gameName;
    createDir("Game/" + _gameName + "/");
    QFile file(fullPath + "/records.txt");
    if (!file.exists()) {
        return;
    }
    file.open(QIODevice::ReadOnly);
    QTextStream textStream(&file);
    textStream.setEncoding(QStringConverter::Utf8);

    struct GameTime record;
    while (!textStream.atEnd()) {
        QString s = textStream.readLine();
        QStringList ss = s.split(" ");
        record.number = ss[0].toInt();
        record.bestScore = ss[1].toInt();
        record.startTime = ss[2];
        record.endTime = ss[3];
        _time.push_back(record);
    }

    file.close();
}

bool Archive::isLogin(QString account, QString password)
{
    QString thisaccount = account;
    QString thisPass = password;

    if(thisPass == nullptr || thisaccount == nullptr){
        return false;
    }

    QFile file("C:/MyGame/user/" + thisaccount + "/" + thisaccount + ".txt");

    file.open(QIODevice::ReadOnly);

    QByteArray data = file.readAll();
    const QString TrulyPass = QString(data);
    QStringList s = TrulyPass.split(":");
    Archive::userName = s.at(0);
    Archive::account = thisaccount;
    file.close();

    if (thisPass == s.at(1)) {
        return true;
    }
    else{
        return false;
    }
}

QVector<GameTime> Archive::getRecords()
{
    return _time;
}

void Archive::createDir(QString path)
{
    QDir dir(PATH + path);
    if (!dir.exists()) {
        dir.mkpath(PATH + path);
    }
}
