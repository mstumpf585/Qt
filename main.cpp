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

    //connect return answer as well as data 1
    //only need to connec the qml to the c++ once
    //Connect from QML to C++
    QObject::connect(window, SIGNAL(qmlRequireData(QString)),
                     &myclass, SLOT(cppGetRequest(QString)));

    //each slot requires a connection to be made, hence the five connections
    //Connect from C++ to QML
    QObject::connect(&myclass, SIGNAL(cppReturnAnswer(QVariant)),
                     window, SLOT(qmlUpdateData(QVariant)));
    //Connect from C++ to QML
    QObject::connect(&myclass, SIGNAL(cppReturnTitle(QVariant)),
                     window, SLOT(qmlUpdateTitle(QVariant)));
    //Connect from C++ to QML
    QObject::connect(&myclass, SIGNAL(cppReturnPrice(QVariant)),
                     window, SLOT(qmlUpdatePrice(QVariant)));
    //Connect from C++ to QML
    QObject::connect(&myclass, SIGNAL(cppReturnTimeRented(QVariant)),
                     window, SLOT(qmlUpdateTime(QVariant)));

    return app.exec();
}
