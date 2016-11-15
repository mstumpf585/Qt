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
        //this is where we define what we are going to send out
        //if it isn't defined in here your cpp can't use it (unless you defin it there
        //but thats just bad coding style
        void cppReturnAnswer(QVariant data);
        void cppReturnTitle(QVariant data);
        void cppReturnPrice(QVariant data);
        void cppReturnTimeRented(QVariant data);

    public slots:
        void cppGetRequest(const QString &msg);

};

#endif // SHAKEHANDS_H
