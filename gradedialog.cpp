#include "gradedialog.h"
#include "ui_gradedialog.h"

GradeDialog::GradeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GradeDialog)
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

    connect(ui->Submit,SIGNAL(clicked()),this,SLOT(submit()));
}

GradeDialog::~GradeDialog()
{
    delete ui;
}
void GradeDialog::submit()
{
    int i=LoginRadioBtnGroup->checkedId();
    QSqlDatabase db = connect_mysql("");
    QSqlQuery query(db);
    qDebug()<<"isopen:"<<db.open();
    qDebug()<<"i是"<<i;
    if(i==1)
    {
        QString insertsentence = "insert into Grade(StuNo,ExpNo,score) values (:StuNo,:ExpNo,:score) ";
        query.prepare(insertsentence);
        query.bindValue(":StuNo",ui->StuNo->text().toInt());
        query.bindValue(":ExpNo",ui->ExpNo->text().toInt());
        query.bindValue(":score",ui->Score->text().toInt());
        //qDebug()<<"InsertSentence:"<<insertsentence;
        query.exec();
        //qDebug()<<"是否valid"<<query.isValid();
        refreshTabelView();
    }
    if(i==2)
    {
        QString delsentence="delete from Grade where StuNo=? and ExpNo=?";
        query.prepare(delsentence);
        query.addBindValue(ui->StuNo->text());
        query.addBindValue(ui->ExpNo->text());
        query.exec();
        refreshTabelView();
    }
    if(i==3)
    {
        QString changesentence = "update Grade set score=? where StuNo=? and ExpNo=?";
        query.prepare(changesentence);
        query.addBindValue(ui->Score->text());
        query.addBindValue(ui->StuNo->text().toInt());
        query.addBindValue(ui->ExpNo->text().toInt());
        query.exec();
        refreshTabelView();
    }
    if(i==4)
    {
        QString searchsentence = "select score from Grade where StuNo = ";
        searchsentence.append(ui->StuNo->text());
        searchsentence.append(" and ExpNo = ");
        searchsentence.append(ui->ExpNo->text());
        qDebug()<<"search_sen"<<searchsentence;
        query.exec(searchsentence);
        query.first();
        ui->Score->setText(query.value("score").toString());
    }
    qDebug()<<"Error:"<<query.lastError().text();
}
void GradeDialog::refreshTabelView()
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
