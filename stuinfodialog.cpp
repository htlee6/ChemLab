#include "stuinfodialog.h"
#include "ui_stuinfodialog.h"

StuInfoDialog::StuInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StuInfoDialog)
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
    //qDebug()<<"ok的状态："<<ok;
    int adm_acc=readAcc();
    //qDebug()<<"tea_acc:"<<adm_acc;
    //qDebug()<<"成功";

    QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
    QString sentence = "select *";
    sentence.append(" from StuInfo");
    //.append(" WHERE Teaching.StuNo = StuInfo.StuNo AND Teaching.TeacherNo=").append(QString::number(adm_acc));
    //qDebug()<<"sentence"<<sentence;
    model->setQuery(sentence);
    //qDebug()<<"行数"<<model->rowCount();
    //qDebug()<<"列数"<<model->columnCount();

    //列名
    model->setHeaderData(0, Qt::Horizontal, "学号");
    model->setHeaderData(1, Qt::Horizontal, "姓名");
    model->setHeaderData(2, Qt::Horizontal, "班级");
    ui->tableView->setModel(model);//数据放置进去
    //ui->tableView->verticalHeader()->hide();//不显示序号
    ui->tableView->show();
    //qDebug()<<"结束";

    connect(ui->Submit,SIGNAL(clicked()),this,SLOT(submit()));
}

StuInfoDialog::~StuInfoDialog()
{
    delete ui;
}
void StuInfoDialog::submit()
{
    int i=LoginRadioBtnGroup->checkedId();
    QSqlDatabase db = connect_mysql("");
    QSqlQuery query(db);
    qDebug()<<"isopen:"<<db.open();
    qDebug()<<"i是"<<i;
    if(i==1)
    {
        QString insertsentence = "insert into StuInfo(StuNo,StuName,Class) values (:StuNo,:StuName,:Class) ";
        query.prepare(insertsentence);
        query.bindValue(":StuNo",ui->StuNo->text().toInt());
        query.bindValue(":StuName",ui->StuName->text());
        query.bindValue(":Class",ui->Class->text());
        //qDebug()<<"InsertSentence:"<<insertsentence;
        query.exec();
        qDebug()<<"是否valid"<<query.isValid();
        refreshTabelView();
    }
    if(i==2)
    {
        QString delsentence="delete from StuInfo where StuNo=?";
        query.prepare(delsentence);
        query.addBindValue(ui->StuNo->text());
        query.exec();
        refreshTabelView();
    }
    if(i==3)
    {
        QString changesentence = "update StuInfo set StuName=?,Class=? where StuNo=?";
        query.prepare(changesentence);
        query.addBindValue(ui->StuName->text());
        query.addBindValue(ui->Class->text());
        query.addBindValue(ui->StuNo->text().toInt());
        query.exec();
        refreshTabelView();
    }
    if(i==4)
    {
        QString searchsentence = "select StuName,Class from StuInfo where StuNo = ";
        searchsentence.append(ui->StuNo->text());
        qDebug()<<"search_sen"<<searchsentence;
        query.exec(searchsentence);
        query.first();
        ui->StuName->setText(query.value("StuName").toString());
        ui->Class->setText(query.value("Class").toString());
    }
    qDebug()<<"Error:"<<query.lastError().text();
}
void StuInfoDialog::refreshTabelView()
{
    QSqlDatabase db = connect_mysql("");
    bool ok=db.open();
    //qDebug()<<"ok的状态："<<ok;
    int adm_acc=readAcc();
    //qDebug()<<"tea_acc:"<<adm_acc;
    //qDebug()<<"成功";

    QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
    QString sentence = "select *";
    sentence.append(" from StuInfo");
    //.append(" WHERE Teaching.StuNo = StuInfo.StuNo AND Teaching.TeacherNo=").append(QString::number(adm_acc));
    //qDebug()<<"sentence"<<sentence;
    model->setQuery(sentence);
    //qDebug()<<"行数"<<model->rowCount();
    //qDebug()<<"列数"<<model->columnCount();

    //列名
    model->setHeaderData(0, Qt::Horizontal, "学号");
    model->setHeaderData(1, Qt::Horizontal, "姓名");
    model->setHeaderData(2, Qt::Horizontal, "班级");
    ui->tableView->setModel(model);//数据放置进去
    //ui->tableView->verticalHeader()->hide();//不显示序号
    ui->tableView->show();
    //qDebug()<<"结束";
}
