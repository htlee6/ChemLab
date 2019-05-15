#ifndef CONNECT_MYSQL_H
#define CONNECT_MYSQL_H

#endif // CONNECT_MYSQL_H
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <QString>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtCore>
#include <QEventLoop>

QSqlDatabase connect_mysql(QString);
QString getGit(QString);

