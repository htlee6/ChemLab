#include "util.h"
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <connect_mysql.h>

void writeAcc(int acc)
{
    QFile file("/Users/Lihaotian/desktop/acc.txt");
    file.open(QIODevice::WriteOnly);
    file.close();
    if(file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream.seek(file.size());
        stream<<QString::number(acc)<<"\n";
        file.close();
    }
    qDebug()<<"文件已写入";
}
void WriteStuNo(QString stuno)
{
    QFile file("/Users/Lihaotian/Desktop/stuno.txt");
    file.open(QIODevice::WriteOnly);
    file.close();
    if(file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream.seek(file.size());
        stream<<stuno;
        file.close();
    }
    qDebug()<<"学号已写入";
}

void WriteExpNo(QString expno)
{
    QFile file("/Users/Lihaotian/Desktop/expno.txt");
    file.open(QIODevice::WriteOnly);
    file.close();
    if(file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream.seek(file.size());
        stream<<expno;
        file.close();
    }
    qDebug()<<"实验号已写入";
}

int readAcc()
{
    QString displayString;
    QFile file("/Users/Lihaotian/Desktop/acc.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Can't open the file!"<<endl;
    }
    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString str(line);
        qDebug()<< str;
        displayString.append(str);
    }
    file.close();
    return displayString.toInt();
}

QString ReadStuNo()
{
    QString displayString;
    QFile file("/Users/Lihaotian/Desktop/stuno.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"读取学号失败"<<endl;
    }
    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString str(line);
        qDebug()<< str;
        displayString.append(str);
    }
    file.close();
    return displayString;
}


QString ReadExpNo()
{
    QString displayString;
    QFile file("/Users/Lihaotian/Desktop/expno.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"读取实验号失败"<<endl;
    }
    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString str(line);
        qDebug()<< str;
        displayString.append(str);
    }
    file.close();
    return displayString;
}
int ifHave(QString datapkgno)
{
    QSqlDatabase dbtest = connect_mysql("");
    QSqlQuery querytest(dbtest);
    QString testsentence = "select count(*) from DataPkg where DataPkgNo = ";
    testsentence.append(datapkgno);
    qDebug()<<"ifHave()中的testsentence"<<testsentence;
    querytest.exec(testsentence);
    querytest.first();
    int count = querytest.value("count(*)").toInt();
    return count;
}
