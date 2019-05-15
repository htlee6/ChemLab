#include "medicineinfodialog.h"
#include "ui_medicineinfodialog.h"

MedicineInfoDialog::MedicineInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MedicineInfoDialog)
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

    connect(ui->Submit,SIGNAL(clicked()),this,SLOT(submit()));
}

MedicineInfoDialog::~MedicineInfoDialog()
{
    delete ui;
}
void MedicineInfoDialog::refreshTabelView()
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
void MedicineInfoDialog::submit()
{
    int i=LoginRadioBtnGroup->checkedId();
    QSqlDatabase db = connect_mysql("");
    QSqlQuery query(db);
    qDebug()<<"isopen:"<<db.open();
    qDebug()<<"i是"<<i;
    if(i==1)
    {
        QString insertsentence = "insert into ChemInfo(ChemNo,ChemName,ChemAmt) values (:ChemNo,:ChemName,:ChemAmt) ";
        query.prepare(insertsentence);
        query.bindValue(":ChemNo",ui->ChemNo->text().toInt());
        query.bindValue(":ChemName",ui->ChemName->text());
        query.bindValue(":ChemAmt",ui->ChemAmt->text());
        //qDebug()<<"InsertSentence:"<<insertsentence;
        query.exec();
        qDebug()<<"是否valid"<<query.isValid();
        refreshTabelView();
    }
    if(i==2)
    {
        QString delsentence="delete from ChemInfo where ChemNo=?";
        query.prepare(delsentence);
        query.addBindValue(ui->ChemNo->text());
        query.exec();
        refreshTabelView();
    }
    if(i==3)
    {
        QString changesentence = "update ChemInfo set ChemName=?,ChemAmt=? where ChemNo=?";
        query.prepare(changesentence);
        query.addBindValue(ui->ChemName->text());
        query.addBindValue(ui->ChemAmt->text());
        query.addBindValue(ui->ChemNo->text().toInt());
        query.exec();
        refreshTabelView();
    }
    if(i==4)
    {
        QString searchsentence = "select ChemName,ChemAmt from ChemInfo where ChemNo = ";
        searchsentence.append(ui->ChemNo->text());
        qDebug()<<"search_sen"<<searchsentence;
        query.exec(searchsentence);
        query.first();
        ui->ChemName->setText(query.value("ChemName").toString());
        ui->ChemAmt->setText(query.value("ChemAmt").toString());
    }
    qDebug()<<"Error:"<<query.lastError().text();
}
