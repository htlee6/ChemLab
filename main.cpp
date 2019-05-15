#include "logindialog.h"
#include "stuwindow.h"
#include "teacherwindow.h"
#include "adminwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginDialog login_dialog;
    StuWindow stu_win;
    TeacherWindow tea_win;
    AdminWindow admin_win;
    login_dialog.show();
    if(login_dialog.exec() == QDialog::Accepted)
    {
        switch (login_dialog.on_loginButton_login_clicked()) {
        case 1:
            stu_win.show();
            stu_win.maximumSize();
            break;
        case 2:
            tea_win.show();
            tea_win.maximumSize();
            break;
        case 3:
            admin_win.show();
            admin_win.maximumSize();
            break;
        default:
            break;
        }
    }

    return a.exec();
}
