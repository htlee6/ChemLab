#include "teacherinfodialog.h"
#include "ui_teacherinfodialog.h"

TeacherInfoDialog::TeacherInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeacherInfoDialog)
{
    ui->setupUi(this);
    add=ui->add;
    del=ui->delete_;
    change=ui->change;
    search=ui->search;

    LoginRadioBtnGroup = new QButtonGroup();
    LoginRadioBtnGroup->addButton(add,1);
    LoginRadioBtnGroup->addButton(del,2);
    LoginRadioBtnGroup->addButton(change,3);
    LoginRadioBtnGroup->addButton(search,4);

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

    connect(ui->Submit,SIGNAL(clicked()),this,SLOT(submit()));
}

TeacherInfoDialog::~TeacherInfoDialog()
{
    delete ui;
}
void TeacherInfoDialog::refreshTabelView()
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
void TeacherInfoDialog::submit()
{
    int i=LoginRadioBtnGroup->checkedId();
    QSqlDatabase db = connect_mysql("");
    QSqlQuery query(db);
    qDebug()<<"isopen:"<<db.open();
    qDebug()<<"i是"<<i;
    if(i==1)
    {
        QString insertsentence = "insert into TeacherInfo(TeacherNo,TeacherName) values (:TeacherNo,:TeacherName) ";
        query.prepare(insertsentence);
        query.bindValue(":TeacherNo",ui->TeaNo->text().toInt());
        query.bindValue(":TeacherName",ui->TeaName->text());
        //qDebug()<<"InsertSentence:"<<insertsentence;
        query.exec();
        qDebug()<<"是否valid"<<query.isValid();
        refreshTabelView();
    }
    if(i==2)
    {
        QString delsentence="delete from TeacherInfo where TeacherNo=?";
        query.prepare(delsentence);
        query.addBindValue(ui->TeaNo->text());
        query.exec();
        refreshTabelView();
    }
    if(i==3)
    {
        QString changesentence = "update TeacherInfo set TeacherName=? where TeacherNo=?";
        query.prepare(changesentence);
        query.addBindValue(ui->TeaName->text());
        query.addBindValue(ui->TeaNo->text().toInt());
        query.exec();
        refreshTabelView();
    }
    if(i==4)
    {
        QString searchsentence = "select TeacherName from TeacherInfo where TeacherNo = ";
        searchsentence.append(ui->TeaNo->text());
        qDebug()<<"search_sen"<<searchsentence;
        query.exec(searchsentence);
        query.first();
        ui->TeaName->setText(query.value("TeacherName").toString());
    }
    qDebug()<<"Error:"<<query.lastError().text();
}
