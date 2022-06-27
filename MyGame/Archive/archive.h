#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <QString>
#include <QTime>
#include <QDateTime>
#include <QFile>
#include <QDir>
#include <QVector>

struct GameTime {
    int number;
    int bestScore;
    QString startTime;
    QString endTime;
};

class Archive
{
public:
    Archive();

    Archive(QString gameName);

    ~Archive();

    QString getGameName();

    void setGameName(QString name);

    void setStartTime(QDateTime startTime);

    void setEndTime(QDateTime endTime);

    int getBestScore();

    void setBestScore(int bestScore);

    int getNumber();

    long getGameTime();

    void writeGameStorage();

    void writeGameRecords();

    void writeUserMessage();

    void readGameStorage();

    void readGameRecords();

    bool isLogin(QString account, QString password);

    bool isRegister(QString account, QString userName, QString password);

    QVector<struct GameTime> getRecords();

    static QString userName;

    static QString account;

    static QString headPath;

    static QString password;

private:

    QString _gameName;

    QVector<struct GameTime> _time;

    QDateTime _startTime;

    QDateTime _endTime;

    int _bestScore;

    int _number;

    long _gameTime;

    const QString PATH = "C:/MyGame/user/";

    void createDir(QString path);
};

#endif // ARCHIVE_H
