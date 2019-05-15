#include "ratingdialog.h"
#include "ui_ratingdialog.h"
#include "util.h"
#include "connect_mysql.h"

#include <QMessageBox>
#include <QSqlDatabase>

RatingDialog::RatingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RatingDialog)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),ui->refreshBtn,SLOT(click()));
    timer->setSingleShot(true);
    timer->start(3000);
    connect(ui->refreshBtn,SIGNAL(clicked()),this,SLOT(ReceiveStuNo()));
    connect(ui->refreshBtn,SIGNAL(clicked()),this,SLOT(ReceiveExpNo()));
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(Rate()));
}

RatingDialog::~RatingDialog()
{
    delete ui;
}

void RatingDialog::ReceiveStuNo()
{
    QString stuno = ReadStuNo();
    ui->StuNoLabel->setText(stuno);
}

void RatingDialog::ReceiveExpNo()
{
    QString expno = ReadExpNo();
    ui->ExpNoLabel->setText(expno);
}

void RatingDialog::Rate()
{

    QSqlDatabase dbtest = connect_mysql("");
    QSqlQuery querytest(dbtest);

    QString testsentence = "select count(*) from Grade where StuNo = ";
    testsentence.append(ui->StuNoLabel->text())
                .append(" and ExpNo = ")
                .append(ui->ExpNoLabel->text());
    qDebug()<<"Sentence"<<testsentence;
    querytest.exec(testsentence);
    querytest.first();
    int count = querytest.value("count(*)").toInt();
    qDebug()<<"Count:"<<count;

    if(count == 0)
    {
        QSqlDatabase db = connect_mysql("");
        QSqlQuery query(db);
        QString insertsentence = "INSERT INTO grade(StuNo,ExpNo,score) VALUES (:StuNo,:ExpNo,:score)";
        query.prepare(insertsentence);
        query.bindValue(":StuNo",ui->StuNoLabel->text().toInt());
        query.bindValue(":ExpNo",ui->ExpNoLabel->text().toInt());
        query.bindValue(":score",ui->ScoreEdit->text().toInt());
        query.exec();
        if(!query.isValid())
            QMessageBox::about(NULL, "评分", "评分成功！");
    }

    if(count != 0)
    {
        QSqlDatabase db = connect_mysql("");
        QSqlQuery query(db);
        QString updatesentence = "update grade set score=? where StuNo=? and ExpNo=?";
        query.prepare(updatesentence);
        query.addBindValue(ui->ScoreEdit->text());
        query.addBindValue(ui->StuNoLabel->text());
        query.addBindValue(ui->ExpNoLabel->text());
        if(!query.isValid())
            QMessageBox::about(NULL, "评分", "评分成功！");
    }
}
