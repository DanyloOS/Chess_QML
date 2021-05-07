#ifndef UCIENGINE_H
#define UCIENGINE_H

#include <QtCore>
#include <QProcess>

#include <iostream>

class UciEngine : public QObject {
    Q_OBJECT
public:
    UciEngine(QObject *parent = 0)
        : QObject(parent)
    {
        m_uciEngine = new QProcess(this);
        m_uciEngine->setProcessChannelMode(QProcess::MergedChannels);
        connect(m_uciEngine, &QIODevice::readyRead, this, &UciEngine::readFromEngine);
        connect(this, &UciEngine::messageReceived, this, &UciEngine::printMessage);
    }

    ~UciEngine()
    {
        m_uciEngine->close();
    }
public slots:
    void startEngine(const QString &enginePath, QStringList argList = QStringList())
    {
        m_uciEngine->start(enginePath, argList);//{"uci", "isready"}));
    }

    void sendCommand(const QString &command)
    {
        qDebug()<<"sendCommand() command = " << command;
        /*qDebug("%lld", */m_uciEngine->write(command.toLatin1());
    }

    void findMove(const QString historyMoves)
    {
        sendCommand("position startpos moves " + historyMoves + "\n");
        sendCommand("go\n");
    }

private slots:
    void readFromEngine()
    {
        while (m_uciEngine->canReadLine())
        {
            QString line = QString::fromLatin1(m_uciEngine->readLine());
            emit messageReceived(line);
            if (line.split(" ").size() >= 2)
                if(line.split(" ").at(0) == "bestmove")
                    emit bestMoveFound(line.split(" ").at(1));
        }
    }

    void printMessage(QString message)
    {
        qDebug("%s", message.toLocal8Bit().data());
//        if (counter++ < 3)
//        {
//            sendCommand(QString::number(counter) + " iteration\n");
//        }
    }


signals:
    void messageReceived(QString);
    void bestMoveFound(QString);
private:
    QProcess *m_uciEngine;

    int counter = 0;
};


#endif // UCIENGINE_H
