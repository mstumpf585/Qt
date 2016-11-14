#include "shakehands.h"
#include <QFile>
#include <QTextStream>
#include <QVector>



typedef struct {
    QString title;
    QString time;
    QString price;

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
    QString moviePrice;
    QString movieTime;
    qDebug() <<"msg from QML: " << msg;


    //if a valid number is entered
    if(((msg.toInt()) %2==0)||((msg.toInt()) %2==1)){
        //do even things
        if(((msg.toInt()) %2==0) && (msg.toInt() != 0)){
            int randomNumber=0;
            randomNumber = rand()%(even.length());
            std::string text = "Even";
            myText = QString::fromStdString(text);
            movieTitle = even[randomNumber].title;
            moviePrice = even[randomNumber].price;
            movieTime = even[randomNumber].time;
            // this is the spot where we need to run our script to get the time
            //then safe it in the movie vector
            //even[randomNumber].time = functionGetTime();


        }
        //do odd things
        if(((msg.toInt())%2==1)&& (msg.toInt() != 0)){
            int randomNumber=0;
            randomNumber = rand()%(odd.length());
            std::string text = "Odd";
            myText = QString::fromStdString(text);
            movieTitle = odd[randomNumber].title;
            moviePrice = odd[randomNumber].price;
            movieTime = odd[randomNumber].time;
            // this is the spot where we need to run our script to get the time
            //then safe it in the movie vector
            //odd[randomNumber].time = functionGetTime();
        }
    }
    //input not valid
    else
    {
        std::string text = "Sorry, but that's not a valid option.";
        myText = QString::fromStdString(text);
    }

    //all of the emit functions are defined in your .h file under the signals.
    //these are the signals that the cpp will be sending to the qml
    //they don't have to have cpp by them but that convention is used to avoid confusion
    //with the qml functions

    //this one will not be necessary when fully functional. left in for testing purposes
    emit cppReturnAnswer(QVariant(myText));
    //send movie title
    emit cppReturnTitle(QVariant(movieTitle));
    //send movie price
    emit cppReturnPrice(QVariant(moviePrice));
    //send movie last rented ( need to write the script that gets current time for that to work.
    emit cppReturnTimeRented(QVariant(movieTime));
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
        //this is the chunk of code that has us skip over lines, assuming we will never
        //see two blank lines in a row
        if(line == "")
            line = in.readLine();
        fields = line.split(";");

        if(i%2 == 0){
            M.title = fields.front();
            M.price = fields.back();
            even.push_back(M);
            evenCount ++;
        }
        if(i%2 == 1){
            M.title = fields.front();
            M.price = fields.back();
            odd.push_back(M);
            oddCount++;
        }
        i++;
    }
    file.close();
}
