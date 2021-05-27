#ifndef UCIENGINE_H
#define UCIENGINE_H

#include <QtCore>
#include <QProcess>

#include <iostream>

class UciEngine : public QObject {
    Q_OBJECT
public:
    enum class UciEngineState {
        None,
        LookingForLegalMoves,
        LookingForTheBestMove
    };

    UciEngine(QObject *parent = 0)
        : QObject(parent), m_buffer(&_m_buffer)
    {
        m_uciEngine = new QProcess(this);
        m_uciEngine->setProcessChannelMode(QProcess::MergedChannels);
        connect(m_uciEngine, &QIODevice::readyRead, this, &UciEngine::readFromEngine);
        connect(this, &UciEngine::messageReceived, this, &UciEngine::parseMessage);
    }

    ~UciEngine()
    {
        m_uciEngine->close();
    }
public slots:
    void startEngine(const QString &enginePath, QStringList argList = QStringList())
    {
        m_uciEngine->start(enginePath, argList);
//        sendCommand("uci\nucinewgame\nisready\n");
//        sendCommand("isready\n");
    }

    void sendCommand(const QString &command)
    {
//        qDebug()<<"sendCommand() command = " << command;
        m_uciEngine->write(command.toLatin1());
    }

    void findMove(const QString previousMoves)
    {
        isLookingForTheBestMove = true;
        sendCommand("position startpos moves " + previousMoves + "\ngo\n");
        QThread::msleep(200);
//        sendCommand("stop\n");
//        QThread::msleep(100);
    }

    void findLegalMoves(const QString previousMoves)
    {
        isLookingForLegalMoves = true;
        sendCommand("position startpos moves " + previousMoves + "\ngo perft 1\n");
    }

private slots:
    void readFromEngine()
    {
        QString legalMoves;

        if (isInitializing)
        {
            while (m_uciEngine->canReadLine())
                m_uciEngine->readAll();
            isInitializing = false;
        }
        else if (isLookingForLegalMoves)
        {
            bool inProcess = true;
            while (m_uciEngine->canReadLine() && isLookingForLegalMoves)
            {
                QString line = QString::fromLatin1(m_uciEngine->readLine());
//                qDebug() << line;
//                m_buffer << line;

                if (line.startsWith("Nodes searched")) inProcess = false;
                else  if (line != "\n") m_buffer << line;
                if (line == "\n" && !inProcess)
                {
                    isLookingForLegalMoves = false;
                    emit messageReceived(UciEngineState::LookingForLegalMoves);
                }
            }
        }
        else if (isLookingForTheBestMove)
        {
            while (m_uciEngine->canReadLine() && isLookingForTheBestMove)
            {
                QString line = QString::fromLatin1(m_uciEngine->readLine());
//                qDebug() << line;
                if (line.startsWith("bestmove"))
                {
                    isLookingForTheBestMove = false;
                    m_buffer << line;
                    emit messageReceived(UciEngineState::LookingForTheBestMove);
                }
            }
        }
    }

    void parseMessage(enum UciEngineState state)
    {
//        qDebug() << "parseMessage begin:\n" << m_buffer.readAll() << "parseMessageEnd\n";
        m_buffer.seek(0);
        switch (state) {
        case UciEngineState::LookingForLegalMoves:
        {
            QString move;
            while (!m_buffer.atEnd())
                move += m_buffer.readLine().split(":").at(0) + " ";
            emit legalMovesFound(move);
            break;
        }
        case UciEngineState::LookingForTheBestMove:
        {
            emit bestMoveFound(m_buffer.readLine().split(" ").at(1));
            break;
        }
        default: break;
        }
//        m_buffer.flush();
        _m_buffer.clear();
//        qDebug() << "parseMessage end: " << m_buffer.readLine();
    }


signals:
    void messageReceived(enum UciEngineState);
    void bestMoveFound(QString);
    void legalMovesFound(QString);

private:
    QProcess *m_uciEngine;
    QString _m_buffer;
    QTextStream m_buffer;
    bool isLookingForLegalMoves = false;
    bool isLookingForTheBestMove = false;
    bool isInitializing = true;
    int counter = 0;
};


#endif // UCIENGINE_H
