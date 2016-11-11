#include "shakehands.h"
#include <QFile>
#include <QTextStream>
#include <QVector>



typedef struct {
    QString title;
    QString time;
    double price;

} movie;

void readFile(QVector <movie> &even, QVector <movie> &odd);

ShakeHands::ShakeHands(QObject *parent) :
    QObject(parent)
{
}

void ShakeHands::cppGetRequest(const QString &msg){

    QVector <movie> even;
    QVector <movie> odd;

    QString myText;
    qDebug() <<"msg from QML: " << msg;

    if((msg.toInt() < 1) || (msg.toInt() > 10)){
        std::string text = "Sorry, but that's not a valid option.";
        myText = QString::fromStdString(text);
    }
    else{//for windows

        readFile(even, odd);

    }
    emit cppReturnAnswer(QVariant(myText));
}

void readFile(QVector <movie> &even, QVector <movie> &odd){

    // open ze file
    //QString myText;
    // QFile file("C:\\Users\\);
    QFile file("/home/michael/lab04again/input.txt");
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "Could not open file";
        return;
    }

    movie M;
    QString line;
    QStringList fields;
    QTextStream in(&file);
    int i=1;
    int oddCount  = 0;
    int evenCount = 0;

    while(!in.atEnd()){

        line = in.readLine();
        fields = line.split(";");

        if(i%2 == 0){

            M.title = fields.front();
            M.price = fields.back().toDouble();
            even.push_back(M);
            qDebug() << even[evenCount].title;

            evenCount ++;

        }else{

            M.title = fields.front();
            M.price = fields.back().toDouble();
            odd.push_back(M);
            qDebug() << odd[oddCount].title << odd[oddCount].price;
            oddCount++;

        }

        i++;
    }

    //myText = QString::fromStdString(quote[msg.toInt()-1]);
    //qDebug() << myText;
    file.close();
}
