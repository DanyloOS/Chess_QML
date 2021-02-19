#include "gameengine.h"

#include <QQmlContext>
#include <QtCore>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

// TODO: find better place for this
#define FEN_START_POS "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    GameEngine gameEngine;
    gameEngine.setUpStartPos(FEN_START_POS);
    engine.rootContext()->setContextProperty("chessBoardModel", &(gameEngine.getChessBoardModel()));
    engine.rootContext()->setContextProperty("chessPieceModel", &(gameEngine.getChessPieceModel()));
    engine.load(url);

    return app.exec();
}
