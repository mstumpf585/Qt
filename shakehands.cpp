#include "shakehands.h"
#include <QFile>
#include <QTextStream>
ShakeHands::ShakeHands(QObject *parent) :
    QObject(parent)
{
}
void ShakeHands::cppGetRequest(const QString &msg){
    qDebug() <<"msg from QML: " << msg;
    QString myText;

    if((msg.toInt() < 1) || (msg.toInt() > 10)){
        std::string text = "Sorry, but that's not a valid option.";
        myText = QString::fromStdString(text);
    }
    else{//for windows
        // QFile file("C:\\Users\\);
        QFile file("/home/michael/workspace/code/input.txt");
        if(!file.open(QFile::ReadOnly | QFile::Text)){
            qDebug() << "Could not open file";
            return;
        }
        QString line;
        std::string quote[10];
        int i=0;
        QTextStream in(&file);
        while(!in.atEnd()){
            line = in.readLine();
            quote[i] = line.toStdString();
            i++;
        }
        myText = QString::fromStdString(quote[msg.toInt()-1]);
        qDebug() << myText;
        file.close();
    }
    emit cppReturnAnswer(QVariant(myText));
}
