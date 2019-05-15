#include "teacherwindow.h"
#include "ui_teacherwindow.h"

#include "logindialog.h"
#include <QString>
#include <QTimer>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QSqlQueryModel>
#include <iostream>
#include <QSqlRecord>
#include <QDesktopServices>
#include "ratingdialog.h"

TeacherWindow::TeacherWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TeacherWindow)
{
    ui->setupUi(this);
    QTimer *teatimer = new QTimer(this);
    connect(teatimer,SIGNAL(timeout()),ui->refreshBtn,SLOT(click()));
    teatimer->setSingleShot(true);
    teatimer->start(1000);
    connect(ui->refreshBtn,SIGNAL(clicked()),this,SLOT(updateNo()));
    //int teacher_acc = updateNo();
    connect(ui->queryBtn,SIGNAL(clicked()),this,SLOT(selectStuInfo()));
    connect(ui->tableView,SIGNAL(clicked(QModelIndex)),this,SLOT(ShowFileDir()));
    connect(ui->ratingBtn,SIGNAL(clicked()),this,SLOT(ShowRatingDialog()));

    /*
    QTableWidget *stuinfo = ui->tableWidget;
    QSqlDatabase db = connect_mysql("");

    QSqlQuery query(db);
    QString sentence = "select StuNo from Teaching where TeacherNo = ";
    sentence.append(QString::number(teacher_acc));
    query.exec(sentence);

    int row=1,col=1;
    while(query.next()){
        for (col;col<=2;col=col+1) {
            if(col==1) {stuinfo->setItem(row,col,QTableWidgetItem(query.value(0).toString()));}
            if(col==2) {stuinfo->setItem(row,col,QTableWidgetItem(query.value(1).toString()));}
        }
    }
    */
}

TeacherWindow::~TeacherWindow()
{
    delete ui;
}
int TeacherWindow::updateNo()
{
    int tea_acc = readAcc();
    ui->acclabel->setText(QString::number(tea_acc));
    QSqlDatabase db = connect_mysql("");
    QString sentence = "Select TeacherName from TeacherInfo where TeacherNo = ";
    sentence.append(QString::number(tea_acc));
    QSqlQuery query(db);
    query.exec(sentence);
    query.first();
    ui->namelabel->setText(query.value("TeacherName").toString());
    return tea_acc;
}
void TeacherWindow::selectStuInfo()
{
    QSqlDatabase db = connect_mysql("");
    bool ok=db.open();
    qDebug()<<"ok的状态："<<ok;
    int tea_acc=readAcc();
    //qDebug()<<"tea_acc:"<<tea_acc;
    //qDebug()<<"成功";

    QString stuno_intext = ui->stuno_Edit->text();//获取学号和实验号
    //qDebug()<<"学号:"<<stuno_intext;
    QString expno_intext = ui->expno_Edit->text();
    //qDebug()<<"实验号:"<<expno_intext;
    QString sentence;

    QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
    if(stuno_intext.compare("")!=0 && expno_intext.compare("")!=0)
    {
        sentence = "select * ";
        sentence.append(" from DataPkg")
                .append(" WHERE DataPkgNo = ")
                .append(stuno_intext)
                .append(expno_intext);
    }
    if(stuno_intext.compare("")!=0 && expno_intext.compare("")==0)
    {
        sentence = "SELECT * FROM datapkg ";
        sentence.append("WHERE DataPkgNo like '")
                .append(stuno_intext)
                .append("_'");
        qDebug()<<"sentence"<<sentence;
    }
    //qDebug()<<"行数"<<model->rowCount();
    //qDebug()<<"列数"<<model->columnCount();
    if(stuno_intext.compare("")==0 && expno_intext.compare("")!=0)
    {
        sentence = "SELECT * FROM datapkg ";
        sentence.append("WHERE DataPkgNo like ")
                .append("'_______")
                .append(expno_intext)
                .append("'");
    }

    qDebug()<<"sentence"<<sentence;

    model->setQuery(sentence);
    //列名
    model->setHeaderData(0, Qt::Horizontal, "实验号");
    model->setHeaderData(1, Qt::Horizontal, "视频号");
    model->setHeaderData(2, Qt::Horizontal, "数据");

    ui->tableView->setModel(model);//数据放置进去
    //ui->tableView->verticalHeader()->hide();//不显示序号
    ui->tableView->show();
    //qDebug()<<"结束";

}
void TeacherWindow::chooseStu()
{
    QSqlQueryModel stuinfo(ui->tableView);
    int row = ui->tableView->currentIndex().row();
    QSqlRecord record = stuinfo.record(row);
    int stu_no = record.value(0).toInt();
    //todo
}
void TeacherWindow::ShowFileDir()
{
    QSqlQueryModel model(ui->tableView);

    QString sentence = "SELECT * FROM datapkg ";
    QString stuno_intext = ui->stuno_Edit->text();//获取学号和实验号
    QString expno_intext = ui->expno_Edit->text();
    sentence.append("WHERE DataPkgNo = ")
            .append(stuno_intext)
            .append(expno_intext);
    model.setQuery(sentence);

    //qDebug()<<"选择单元格过程row："<<ui->tableView->currentIndex().row();
    //qDebug()<<"选择单元格过程col："<<ui->tableView->currentIndex().column();
    int row = ui->tableView->currentIndex().row();
    QSqlRecord record = model.record(row);

    if(ui->tableView->currentIndex().column()==2)
    {
        qDebug()<<"选文档";
        QString filedir = record.value(2).toString();
        qDebug()<<"filedir is "<<filedir;
        QString filedi = "file:///";
        if(filedir.compare("")!=0)
        {
            QDesktopServices::openUrl(QUrl(filedi.append(filedir), QUrl::TolerantMode));
            qDebug()<<"文件地址:"<<QUrl(filedi.append(filedir));
        }
    }
    if(ui->tableView->currentIndex().column()==1)
    {
        qDebug()<<"选视频";
        QString filedir = record.value(1).toString();
        qDebug()<<"filedir is "<<filedir;
        //QString filedi = "file:///";
        if(filedir.compare("")!=0)
        {
            QDesktopServices::openUrl(QUrl(filedir, QUrl::TolerantMode));
            qDebug()<<"文件地址:"<<QUrl(filedir);
        }
    }
}

void TeacherWindow::ShowRatingDialog()
{
    QString stuno_intext = ui->stuno_Edit->text();
    QString expno_intext = ui->expno_Edit->text();
    if(stuno_intext != NULL)
    {
        WriteStuNo(stuno_intext);
        WriteExpNo(expno_intext);

        rate.exec();
     }
     else {
        QMessageBox::about(NULL, "错误", "请先选择学生");
     }
}
