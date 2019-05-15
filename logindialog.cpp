#include "logindialog.h"
#include "ui_logindialog.h"
#include "login.h"
#include "util.h"

//int stuNo;

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    rBtn_stu = ui->stu_radioBtn;
    rBtn_tea = ui->teacher_radioBtn;
    rBtn_admin = ui->admin_radioBtn;

    acc_LineEdit = ui->acc_Edit;
    pwd_LineEdit = ui->pwd_Edit;

    loginBtn = ui->loginButton;

    //已在.h中声明
    //建立一个QButtonGroup
    LoginRadioBtnGroup = new QButtonGroup(this);
    //抽象的QRadioButton指向已创建的部件
    //向ButtonGroup里加入Button
    LoginRadioBtnGroup->addButton(rBtn_stu,identity_stu);
    LoginRadioBtnGroup->addButton(rBtn_tea,identity_tea);
    LoginRadioBtnGroup->addButton(rBtn_admin,identity_admin);

    connect(loginBtn,SIGNAL(clicked()),this,SLOT(on_loginButton_login_clicked()));
    connect(NULL,NULL,this,SLOT(accept()));
    //stuNo = *tempno;
}

LoginDialog::~LoginDialog()
{
    delete ui;
}
int LoginDialog::on_loginButton_login_clicked()
{
    int acc_intext = ui->acc_Edit->text().toInt();
        qDebug()<<"账号:"<<acc_intext;
        QString pwd_intext = ui->pwd_Edit->text();
        qDebug()<<"密码:"<<pwd_intext;
        int identity = LoginRadioBtnGroup->checkedId();
        //qDebug()<<identity;
        QString identity_str;
        switch(identity)
        {
            case identity_stu:
                identity_str="student";
                qDebug()<<"身份:学生";
            break;
            case identity_tea:
                identity_str="teacher";
                qDebug()<<"身份:教师";
            break;
            case identity_admin:
                identity_str="admin";
                qDebug()<<"身份:管理员";
            break;
            default:break;
        }
        QSqlDatabase db_login = connect_mysql("");
        int LoginStateCode = loginState(acc_intext,pwd_intext,identity_str,db_login);
        checkLoginState(LoginStateCode);

        if(LoginStateCode == 1){
            QMessageBox::information(this,"登录状态","登陆成功！");
            writeAcc(acc_intext);
            this->accept();
        }
        if(LoginStateCode == 0){
            QMessageBox::information(this,"登录状态","无此用户。");
        }
        if(LoginStateCode == -1){
            QMessageBox::information(this,"登录状态","密码错误！");
        }

        emit sendStuNo(ui->acc_Edit->text().toInt());

        return identity;
}


