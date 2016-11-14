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
    readFile(even, odd);
    QString myText;
    QString movieTitle;
    //QString movieprice;
    qDebug() <<"msg from QML: " << msg;

    //do even or odd things
    if(((msg.toInt()) %2==0)||((msg.toInt()) %2==1)){
        //do even things
        if(((msg.toInt()) %2==0&& (msg.toInt() != 0))){
            //real logic later, return title and prices and move on
            qDebug() << "This is where we would do even things";
            qDebug() << msg.toInt();
            std::string text = "Even";
            myText = QString::fromStdString(text);
            movieTitle = even[msg.toInt()].title;

        }
        //do odd things
        if(((msg.toInt())%2==1)&& (msg.toInt() != 0)){
            //real logic later, return title and prices and move on
            qDebug() << "This is where we would do odd things";
            qDebug() << msg.toInt();
            std::string text = "Odd";
            myText = QString::fromStdString(text);
            movieTitle = odd[msg.toInt()].title;
        }
    }
    //input not valid
    else
    {
        std::string text = "Sorry, but that's not a valid option.";
        myText = QString::fromStdString(text);
    }

    emit cppReturnAnswer(QVariant(myText));
    //send movie title
    //emit cppReturnTitle(QVariant(movieTitle));
    //send movie price
    //emit cppReturnPrice(QVariant(moviePrice));
    //send movie last rented ( need to write the script that gets current time for that to work.
}

void readFile(QVector <movie> &even, QVector <movie> &odd){

    QFile file("/home/kevin/Desktop/Qt/input.txt");
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
        if(line == "")
            line = in.readLine();
        fields = line.split(";");

        if(i%2 == 0){
            M.title = fields.front();
            M.price = fields.back().toDouble();
            even.push_back(M);
            evenCount ++;
        }
        if(i%2 == 1){
            M.title = fields.front();
            M.price = fields.back().toDouble();
            odd.push_back(M);
            oddCount++;
        }
        i++;
    }
    file.close();
}
