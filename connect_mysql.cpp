#include "connect_mysql.h"
#include <QtCore>
QSqlDatabase connect_mysql(QString secret)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    //db.setHostName("138.68.232.7");
    //db.setUserName("lht");
    //db.setPassword(secret);
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setUserName("root");
    db.setDatabaseName("misDB");
    db.setPassword("yy23876563");
    db.open();
    if(!db.open()) {
        qDebug()<<"不能连接数据库"<<db.lastError().text();
        //return ;
    }
    else {
        qDebug()<<"连接数据库成功";
    }
    //QSqlQuery query(db);
    //query.exec("select * from stuinfo");
    //while(query.next()){
    //    qDebug()<<query.value("StuNo").toString();
    //}
    return db;
}
QString getGit(QString URLSTR){
    QUrl url(URLSTR);
    QNetworkAccessManager manager;
    QEventLoop loop;

    QNetworkReply *reply = manager.get(QNetworkRequest(url));
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    QString codeContent = reply->readAll();

    return codeContent;
}

