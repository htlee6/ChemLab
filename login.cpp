#include "login.h"

int loginState(int Num, QString pwd, QString identity, QSqlDatabase db){
    int count = 0;
    int state = 100; //1代表成功,0无此账号，-1密码错误
    //compare=0说明字符串相同，=1说明不同

    //qDebug()<<"QString identity:"<<identity;
    //qDebug()<<"与student字符串比"<<identity.compare("student");
    if(identity.compare("student") == 0){

        qDebug()<<"进入学生查询";
        QSqlQuery query_stu(db);
        QString sentence_stu="select Pwd from StuLogin where StuNo =";
        sentence_stu.append(QString::number(Num));
        //qDebug()<<"学生登录查询语句:"<<sentence_stu;
        query_stu.exec(sentence_stu);
        while(query_stu.next()){ count++; }

        query_stu.first();
        qDebug()<<"pwd:"<<pwd;
        qDebug()<<"数据库查到的密码:"<<query_stu.value("Pwd").toString();
        //qDebug()<<pwd.compare(query_stu.value("Pwd").toString());
        if(count == 1 && !pwd.compare(query_stu.value("Pwd").toString()) ){state = 1;} //成功登录
        if(count == 1 && pwd.compare(query_stu.value("Pwd").toString()) ){state = -1;} //密码错误
        if(count == 0){state = 0;} //无此账号

    }

    if(identity.compare("teacher") == 0){

        qDebug()<<"进入教师查询";
        QSqlQuery query_teacher(db);
        QString sentence_teacher="select Pwd from TeacherLogin where TeacherNo =";
        sentence_teacher.append(QString::number(Num));
        query_teacher.exec(sentence_teacher);
        while(query_teacher.next()){ count++; }
        query_teacher.first();

        qDebug()<<"pwd:"<<pwd;
        qDebug()<<"数据库查到的密码:"<<query_teacher.value("Pwd").toString();
        //qDebug()<<pwd.compare(query_teacher.value("Pwd").toString());
        if(count == 1 && !pwd.compare(query_teacher.value("Pwd").toString()) ){state = 1;} //成功登录
        if(count == 1 && pwd.compare(query_teacher.value("Pwd").toString()) ){state = -1;} //密码错误
        if(count == 0){state = 0;} //无此账号

    }

    if(identity.compare("admin") == 0){

        qDebug()<<"进入管理员查询";
        QSqlQuery query_admin(db);
        QString sentence_admin="select Pwd from AdminLogin where AdminNo =";
        sentence_admin.append(QString::number(Num));

        query_admin.exec(sentence_admin);
        while(query_admin.next()){ count++; }
        query_admin.first();

        qDebug()<<"pwd:"<<pwd;
        qDebug()<<"数据库查到的密码:"<<query_admin.value("Pwd").toString();
        //qDebug()<<pwd.compare(query_admin.value("Pwd").toString());
        if(count == 1 && !pwd.compare(query_admin.value("Pwd").toString()) ){state = 1;} //成功登录
        if(count == 1 && pwd.compare(query_admin.value("Pwd").toString()) ){state = -1;} //密码错误
        if(count == 0){state = 0;} //无此账号

    }
    return state;
}

void checkLoginState(int LoginStateCode)
{
    if (LoginStateCode == 1 )
        qDebug()<<"登陆成功,登录状态码是1.";
    if (LoginStateCode == 0)
        qDebug()<<"无此账号,登录状态码是0";
    if (LoginStateCode == -1)
        qDebug()<<"密码错误,登录状态码是-1";
    if (LoginStateCode == 100)
        qDebug()<<"状态码为初始值100,没起作用?";
}
