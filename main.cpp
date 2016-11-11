#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtDebug>
#include <QQuickView>
#include "shakehands.h"
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{
    ShakeHands myclass;
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));


    QObject *topLevel = engine.rootObjects().at(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);

    //Connect from QML to C++
    QObject::connect(window, SIGNAL(qmlRequireData(QString)),
                     &myclass, SLOT(cppGetRequest(QString)));
    //Connect from C++ to QML
    QObject::connect(&myclass, SIGNAL(cppReturnAnswer(QVariant)),
                     window, SLOT(qmlUpdateData(QVariant)));

    return app.exec();
}
