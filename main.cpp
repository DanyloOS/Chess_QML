#include "gameengine.h"

#include <QQmlContext>
#include <QtCore>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

void TestFEN();

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

//    TestFEN();

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    GameEngine gameEngine;
    engine.rootContext()->setContextProperty("chessBoardModel", &(gameEngine.getChessBoardModel()));
    engine.load(url);

    return app.exec();
}

void TestFEN()
{
    QString res = FEN::fromBoardToFEN(FEN::fromFENToBoard(CHESS_DEFAULT_FEN));
    qDebug("%s\n%s", CHESS_DEFAULT_FEN, res.toStdString().c_str());
    getchar();
}
