#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    QTimer *admtimer = new QTimer(this);
    connect(admtimer,SIGNAL(timeout()),ui->refreshBtn,SLOT(click()));
    admtimer->setSingleShot(true);
    admtimer->start(1000);

    /*
    add = ui->add_rBtn;
    del = ui->delete_rBtn;
    change = ui->change_rBtn;
    search = ui->search_rBtn;

    LoginRadioBtnGroup = new QButtonGroup;
    LoginRadioBtnGroup->addButton(add,1);
    LoginRadioBtnGroup->addButton(del,2);
    LoginRadioBtnGroup->addButton(change,3);
    LoginRadioBtnGroup->addButton(search,4);
    */

    connect(ui->refreshBtn,SIGNAL(clicked()),this,SLOT(updateNo()));
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(comboxChange()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(tiaozhuan()));
    connect(ui->refreshTableView,SIGNAL(clicked()),this,SLOT(comboxChange()));
}

AdminWindow::~AdminWindow()
{
    delete ui;
}
int AdminWindow::updateNo()
{
    int admin_acc = readAcc();
    ui->acclabel->setText(QString::number(admin_acc));
    QSqlDatabase db = connect_mysql("");
    QString sentence = "Select AdminName from AdminInfo where AdminNo = ";
    sentence.append(QString::number(admin_acc));
    QSqlQuery query(db);
    query.exec(sentence);
    query.first();
    ui->namelabel->setText(query.value("AdminName").toString());
    return admin_acc;
}
void AdminWindow::selectStuInfo()
{
    QSqlDatabase db = connect_mysql("");
    bool ok=db.open();
    qDebug()<<"ok的状态："<<ok;
    int adm_acc=readAcc();
    qDebug()<<"tea_acc:"<<adm_acc;
    qDebug()<<"成功";

    QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
    QString sentence = "select *";
    sentence.append(" from StuInfo");
    //.append(" WHERE Teaching.StuNo = StuInfo.StuNo AND Teaching.TeacherNo=").append(QString::number(adm_acc));
    qDebug()<<"sentence"<<sentence;
    model->setQuery(sentence);
    qDebug()<<"行数"<<model->rowCount();
    qDebug()<<"列数"<<model->columnCount();

    //列名
    model->setHeaderData(0, Qt::Horizontal, "学号");
    model->setHeaderData(1, Qt::Horizontal, "姓名");
    model->setHeaderData(2, Qt::Horizontal, "班级");
    ui->tableView->setModel(model);//数据放置进去
    //ui->tableView->verticalHeader()->hide();//不显示序号
    ui->tableView->show();
    qDebug()<<"结束";
}
void AdminWindow::selectTeaInfo()
{
    QSqlDatabase db = connect_mysql("");
    bool ok=db.open();
    qDebug()<<"ok的状态："<<ok;
    int adm_acc=readAcc();
    qDebug()<<"tea_acc:"<<adm_acc;
    qDebug()<<"成功";

    QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
    QString sentence = "select *";
    sentence.append(" from TeacherInfo");
    //.append(" WHERE Teaching.StuNo = StuInfo.StuNo AND Teaching.TeacherNo=").append(QString::number(adm_acc));
    qDebug()<<"sentence"<<sentence;
    model->setQuery(sentence);
    qDebug()<<"行数"<<model->rowCount();
    qDebug()<<"列数"<<model->columnCount();

    //列名
    model->setHeaderData(0, Qt::Horizontal, "教师编号");
    model->setHeaderData(1, Qt::Horizontal, "姓名");
    ui->tableView->setModel(model);//数据放置进去
    //ui->tableView->verticalHeader()->hide();//不显示序号
    ui->tableView->show();
    qDebug()<<"结束";
}
void AdminWindow::selectStuLoginInfo()
{
    QSqlDatabase db = connect_mysql("");
    bool ok=db.open();
    qDebug()<<"ok的状态："<<ok;
    int adm_acc=readAcc();
    qDebug()<<"tea_acc:"<<adm_acc;
    qDebug()<<"成功";

    QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
    QString sentence = "select *";
    sentence.append(" from Stulogin");
    //.append(" WHERE Teaching.StuNo = StuInfo.StuNo AND Teaching.TeacherNo=").append(QString::number(adm_acc));
    qDebug()<<"sentence"<<sentence;
    model->setQuery(sentence);
    qDebug()<<"行数"<<model->rowCount();
    qDebug()<<"列数"<<model->columnCount();

    //列名
    model->setHeaderData(0, Qt::Horizontal, "学号");
    model->setHeaderData(1, Qt::Horizontal, "密码");
    //model->setHeaderData(2, Qt::Horizontal, "班级");
    ui->tableView->setModel(model);//数据放置进去
    //ui->tableView->verticalHeader()->hide();//不显示序号
    ui->tableView->show();
    qDebug()<<"结束";
}
void AdminWindow::selectTeaLoginInfo()
{
    QSqlDatabase db = connect_mysql("");
    bool ok=db.open();
    qDebug()<<"ok的状态："<<ok;
    int adm_acc=readAcc();
    qDebug()<<"tea_acc:"<<adm_acc;
    qDebug()<<"成功";

    QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
    QString sentence = "select *";
    sentence.append(" from TeacherLogin");
    //.append(" WHERE Teaching.StuNo = StuInfo.StuNo AND Teaching.TeacherNo=").append(QString::number(adm_acc));
    qDebug()<<"sentence"<<sentence;
    model->setQuery(sentence);
    qDebug()<<"行数"<<model->rowCount();
    qDebug()<<"列数"<<model->columnCount();

    //列名
    model->setHeaderData(0, Qt::Horizontal, "教师编号");
    model->setHeaderData(1, Qt::Horizontal, "密码");
    //model->setHeaderData(2, Qt::Horizontal, "班级");
    ui->tableView->setModel(model);//数据放置进去
    //ui->tableView->verticalHeader()->hide();//不显示序号
    ui->tableView->show();
    qDebug()<<"结束";
}
void AdminWindow::selectMedicinInfo()
{
    QSqlDatabase db = connect_mysql("");
    bool ok=db.open();
    qDebug()<<"ok的状态："<<ok;
    int adm_acc=readAcc();
    qDebug()<<"tea_acc:"<<adm_acc;
    qDebug()<<"成功";

    QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
    QString sentence = "select *";
    sentence.append(" from ChemInfo");
    //.append(" WHERE Teaching.StuNo = StuInfo.StuNo AND Teaching.TeacherNo=").append(QString::number(adm_acc));
    qDebug()<<"sentence"<<sentence;
    model->setQuery(sentence);
    qDebug()<<"行数"<<model->rowCount();
    qDebug()<<"列数"<<model->columnCount();

    //列名
    model->setHeaderData(0, Qt::Horizontal, "药品编号");
    model->setHeaderData(1, Qt::Horizontal, "药品名");
    model->setHeaderData(2, Qt::Horizontal, "剩余数量");
    ui->tableView->setModel(model);//数据放置进去
    //ui->tableView->verticalHeader()->hide();//不显示序号
    ui->tableView->show();
    qDebug()<<"结束";
}
void AdminWindow::selectEquipmentInfo()
{
    QSqlDatabase db = connect_mysql("");
    bool ok=db.open();
    qDebug()<<"ok的状态："<<ok;
    int adm_acc=readAcc();
    qDebug()<<"tea_acc:"<<adm_acc;
    qDebug()<<"成功";

    QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
    QString sentence = "select *";
    sentence.append(" from EquipInfo");
    //.append(" WHERE Teaching.StuNo = StuInfo.StuNo AND Teaching.TeacherNo=").append(QString::number(adm_acc));
    qDebug()<<"sentence"<<sentence;
    model->setQuery(sentence);
    qDebug()<<"行数"<<model->rowCount();
    qDebug()<<"列数"<<model->columnCount();

    //列名
    model->setHeaderData(0, Qt::Horizontal, "仪器编号");
    model->setHeaderData(1, Qt::Horizontal, "仪器名");
    model->setHeaderData(2, Qt::Horizontal, "剩余数量");
    ui->tableView->setModel(model);//数据放置进去
    //ui->tableView->verticalHeader()->hide();//不显示序号
    ui->tableView->show();
    qDebug()<<"结束";
}
void AdminWindow::selectTeachingInfo()
{
    QSqlDatabase db = connect_mysql("");
    bool ok=db.open();
    qDebug()<<"ok的状态："<<ok;
    int adm_acc=readAcc();
    qDebug()<<"tea_acc:"<<adm_acc;
    qDebug()<<"成功";

    QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
    QString sentence = QString("SELECT TeacherInfo.TeacherNo,TeacherInfo.TeacherName,StuInfo.StuNo,StuInfo.StuName")
            .append(" FROM Teaching,TeacherInfo,StuInfo")
            .append(" WHERE Teaching.StuNo=StuInfo.StuNo")
            .append(" AND Teaching.TeacherNo=TeacherInfo.TeacherNo");
    //sentence.append(" from Stulogin");
    //.append(" WHERE Teaching.StuNo = StuInfo.StuNo AND Teaching.TeacherNo=").append(QString::number(adm_acc));
    qDebug()<<"sentence"<<sentence;
    model->setQuery(sentence);
    qDebug()<<"行数"<<model->rowCount();
    qDebug()<<"列数"<<model->columnCount();

    //列名
    model->setHeaderData(0, Qt::Horizontal, "教师号码");
    model->setHeaderData(1, Qt::Horizontal, "教师姓名");
    model->setHeaderData(2, Qt::Horizontal, "学号");
    model->setHeaderData(3, Qt::Horizontal, "学生姓名");
    ui->tableView->setModel(model);//数据放置进去
    //ui->tableView->verticalHeader()->hide();//不显示序号
    ui->tableView->show();
    qDebug()<<"结束";
}
void AdminWindow::selectGrade()
{
    QSqlDatabase db = connect_mysql("");
    bool ok=db.open();
    qDebug()<<"ok的状态："<<ok;
    int adm_acc=readAcc();
    qDebug()<<"tea_acc:"<<adm_acc;
    qDebug()<<"成功";

    QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
    QString sentence = "select Grade.StuNo,Grade.ExpNo,Grade.score,Teaching.TeacherNo,TeacherInfo.TeacherName from Grade,Teaching,TeacherInfo where Teaching.StuNo = Grade.StuNo and Teaching.TeacherNo = TeacherInfo.TeacherNo";
    //.append(" WHERE Teaching.StuNo = StuInfo.StuNo AND Teaching.TeacherNo=").append(QString::number(adm_acc));
    qDebug()<<"sentence"<<sentence;
    model->setQuery(sentence);
    qDebug()<<"行数"<<model->rowCount();
    qDebug()<<"列数"<<model->columnCount();

    //列名
    model->setHeaderData(0, Qt::Horizontal, "学号");
    model->setHeaderData(1, Qt::Horizontal, "实验编号");
    model->setHeaderData(2, Qt::Horizontal, "成绩");
    model->setHeaderData(3, Qt::Horizontal, "教师编号");
    model->setHeaderData(4, Qt::Horizontal, "教师姓名");
    ui->tableView->setModel(model);//数据放置进去
    //ui->tableView->verticalHeader()->hide();//不显示序号
    ui->tableView->show();
    qDebug()<<"结束";
}
void AdminWindow::comboxChange()
{
    qDebug()<<"CurrentIndex"<<ui->comboBox->currentIndex();
    int index = ui->comboBox->currentIndex();
    if(index==1){selectStuInfo();}
    if(index==2){selectStuLoginInfo();}
    if(index==3){selectTeaInfo();}
    if(index==4){selectTeaLoginInfo();}
    if(index==5){selectMedicinInfo();}
    if(index==6){selectEquipmentInfo();}
    if(index==7){selectTeachingInfo();}
    if(index==8){selectGrade();}

}
void AdminWindow::tiaozhuan()
{
    if(ui->comboBox->currentIndex()==1)
    {
        StuInfoDialog stuinfodia;
        stuinfodia.exec();
    }
    if(ui->comboBox->currentIndex()==2)
    {
        StuLoginInfoDialog stulogininfodia;
        stulogininfodia.exec();
    }
    if(ui->comboBox->currentIndex()==3)
    {
        TeacherInfoDialog teacherinfodia;
        teacherinfodia.exec();
    }
    if(ui->comboBox->currentIndex()==4)
    {
        TeacherLoginInfoDialog stuinfodia;
        stuinfodia.exec();
    }
    if(ui->comboBox->currentIndex()==5)
    {
        MedicineInfoDialog stuinfodia;
        stuinfodia.exec();
    }
    if(ui->comboBox->currentIndex()==6)
    {
        EquipmentInfoDialog stuinfodia;
        stuinfodia.exec();
    }
    if(ui->comboBox->currentIndex()==7)
    {
        TeachingInfoDialog stuinfodia;
        stuinfodia.exec();
    }
    if(ui->comboBox->currentIndex()==8)
    {
        GradeDialog stuinfodia;
        stuinfodia.exec();
    }
}
int AdminWindow::modeSelect()
{
    //return LoginRadioBtnGroup->checkedId();
}
