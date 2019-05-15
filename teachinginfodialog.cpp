#include "teachinginfodialog.h"
#include "ui_teachinginfodialog.h"

TeachingInfoDialog::TeachingInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TeachingInfoDialog)
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

    connect(ui->Submit,SIGNAL(clicked()),this,SLOT(submit()));

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

TeachingInfoDialog::~TeachingInfoDialog()
{
    delete ui;
}
void TeachingInfoDialog::refreshTabelView()
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
void TeachingInfoDialog::submit()
{
    int i=LoginRadioBtnGroup->checkedId();
    QSqlDatabase db = connect_mysql("");
    QSqlQuery query(db);
    qDebug()<<"isopen:"<<db.open();
    qDebug()<<"i是"<<i;
    if(i==1)
    {
        QString insertsentence = "insert into Teaching(StuNo,TeacherNo) values (:StuNo,:TeachingNo) ";
        query.prepare(insertsentence);
        query.bindValue(":StuNo",ui->StuNo->text().toInt());
        query.bindValue(":TeachingNo",ui->TeaNo->text());
        //qDebug()<<"InsertSentence:"<<insertsentence;
        query.exec();
        qDebug()<<"是否valid"<<query.isValid();
        refreshTabelView();
    }
    if(i==2)
    {
        QString delsentence="delete from Teaching where StuNo=? and TeacherNo =?";
        query.prepare(delsentence);
        query.addBindValue(ui->StuNo->text());
        query.addBindValue(ui->TeaNo->text());
        query.exec();
        refreshTabelView();
    }
    if(i==3)
    {
        QString changesentence = "update Teaching set TeacherNo=? where StuNo=?";
        query.prepare(changesentence);
        query.addBindValue(ui->TeaNo->text().toInt());
        query.addBindValue(ui->StuNo->text().toInt());
        query.exec();
        refreshTabelView();
    }
    if(i==4)
    {
        QString searchsentence = "select TeacherNo from Teaching where StuNo = ";
        searchsentence.append(ui->StuNo->text());
        qDebug()<<"search_sen"<<searchsentence;
        query.exec(searchsentence);
        query.first();
        ui->TeaNo->setText(query.value("TeacherNo").toString());
    }
    qDebug()<<"Error:"<<query.lastError().text();
}
