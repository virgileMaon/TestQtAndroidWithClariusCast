#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "castbridgeandroid.h"
#include "castbridgefake.h"

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);
    auto cast_bridge = new CastBridgeAndroid(&app);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/TestWithClariusCast10/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    auto qmlContext = engine.rootContext();

    qmlContext->setContextProperty("cast_", cast_bridge);

    engine.load(url);

    auto result = app.exec();
    return result;
}
