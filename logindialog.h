#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QButtonGroup>
#include <QRadioButton>
#include <QDebug>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

#include "connect_mysql.h"
#include "login.h"


namespace Ui {
class LoginDialog;

}

class LoginDialog : public QDialog
{

    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    typedef enum{
        identity_stu=1,
        identity_tea=2,
        identity_admin=3,
    }indentity_code;

    QButtonGroup *LoginRadioBtnGroup;

    QRadioButton *rBtn_stu, *rBtn_tea, *rBtn_admin;
    QLineEdit *acc_LineEdit,*pwd_LineEdit;
    QPushButton *loginBtn;


public slots:
    int on_loginButton_login_clicked();

signals:
    void sendStuNo(int stuNo);

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
