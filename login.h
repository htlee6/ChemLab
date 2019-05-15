#ifndef LOGIN_H
#define LOGIN_H

#endif // LOGIN_H

#include <QtCore>
#include "connect_mysql.h"

int loginState(int Num, QString pwd, QString identity,QSqlDatabase db);
void checkLoginState(int LoginStateCode);
