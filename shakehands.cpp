#include "shakehands.h"
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QTime>



typedef struct {
    QString title;
    QString time;
    QString price;

} movie;

void readFile(QVector <movie> &even, QVector <movie> &odd);
QString getTime();
std::string getCmdOutput(const std::string& mStr);

ShakeHands::ShakeHands(QObject *parent) :
    QObject(parent)
{
}

static int doOnce =0;

void ShakeHands::cppGetRequest(const QString &msg){


    static QVector <movie> even;
    static QVector <movie> odd;
    if(doOnce <1){
    readFile(even, odd);
    }
    QString myText;
    QString movieTitle;
    QString moviePrice;
    QString movieTime;
    qDebug() <<"msg from QML: " << msg;


    //if a valid number is entered
    if(((msg.toInt()) %2==0)||((msg.toInt()) %2==1)){
        int randomNumber=0;
        qsrand(static_cast<uint>(QTime::currentTime().msec()));

        //do even things
        if(((msg.toInt()) %2==0) && (msg.toInt() != 0)){
            randomNumber = rand()%(even.length());
            movieTitle = even[randomNumber].title;
            moviePrice = even[randomNumber].price;
            movieTime = even[randomNumber].time;
            even[randomNumber].time = getTime();
            qDebug()<< even[randomNumber].time;
        }
        //do odd things
        if(((msg.toInt())%2==1)&& (msg.toInt() != 0)){

            randomNumber = rand()%(odd.length());
            movieTitle = odd[randomNumber].title;
            moviePrice = odd[randomNumber].price;
            movieTime = odd[randomNumber].time;
            odd[randomNumber].time = getTime();
            qDebug()<< odd[randomNumber].time;
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

QString getTime(){
    QString returnValue;
    //std::string text = getCmdOutput("/home/kevin/Desktop/Qt/myTime.sh");
    std::string text = getCmdOutput("/home/michael/lab04again/myTime.sh");
    returnValue = QString::fromStdString(text);
    return returnValue;
}

//found from stack overflow, calling bash scripts is easy
//getting them to give you a return value is the awful part
std::string getCmdOutput(const std::string& mStr)
{
    std::string result, file;
    FILE* pipe{popen(mStr.c_str(), "r")};
    char buffer[256];

    while(fgets(buffer, sizeof(buffer), pipe) != NULL)
    {
        file = buffer;
        result += file.substr(0, file.size() - 1);
    }

    pclose(pipe);
    return result;

}

void readFile(QVector <movie> &even, QVector <movie> &odd){

    //QFile file("/home/kevin/Desktop/Qt/input.txt");
    QFile file("/home/michael/lab04again/input.txt");
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "Could not open file";
        return;
    }
    doOnce++;

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
            M.time = "Never Rented";
            even.push_back(M);
            evenCount ++;
        }
        if(i%2 == 1){
            M.title = fields.front();
            M.price = fields.back();
            M.time = "Never Rented";
            odd.push_back(M);
            oddCount++;
        }
        i++;
    }
    file.close();
}
