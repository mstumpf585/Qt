#ifndef SHAKEHANDS_H
#define SHAKEHANDS_H

#include <QObject>
#include <QDebug>

class ShakeHands : public QObject
{
    Q_OBJECT
    public:
        explicit ShakeHands(QObject *parent = 0);
        int updateColor;
    signals:
        void cppReturnAnswer(QVariant data);
    public slots:
        void cppGetRequest(const QString &msg);

};

#endif // SHAKEHANDS_H
