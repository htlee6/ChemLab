#include "equipmentinfodialog.h"
#include "ui_equipmentinfodialog.h"

EquipmentInfoDialog::EquipmentInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EquipmentInfoDialog)
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

    connect(ui->Submit,SIGNAL(clicked()),this,SLOT(submit()));
}

EquipmentInfoDialog::~EquipmentInfoDialog()
{
    delete ui;
}
void EquipmentInfoDialog::submit()
{
    int i=LoginRadioBtnGroup->checkedId();
    QSqlDatabase db = connect_mysql("");
    QSqlQuery query(db);
    //qDebug()<<"isopen:"<<db.open();
    qDebug()<<"i是"<<i;
    if(i==1)
    {
        QString insertsentence = "insert into EquipInfo(EquipNo,EquipName,EquipAmt) values (:EquipNo,:EquipName,:EquipAmt) ";
        query.prepare(insertsentence);
        query.bindValue(":EquipNo",ui->EquipNo->text().toInt());
        query.bindValue(":EquipName",ui->EquipName->text());
        query.bindValue(":EquipAmt",ui->EquipAmt->text());
        //qDebug()<<"InsertSentence:"<<insertsentence;
        query.exec();
        //qDebug()<<"是否valid"<<query.isValid();
        refreshTabelView();
    }
    if(i==2)
    {
        QString delsentence="delete from EquipInfo where EquipNo=?";
        query.prepare(delsentence);
        query.addBindValue(ui->EquipNo->text());
        query.exec();
        refreshTabelView();
    }
    if(i==3)
    {
        QString changesentence = "update EquipInfo set EquipName=?,EquipAmt=? where EquipNo=?";
        query.prepare(changesentence);
        query.addBindValue(ui->EquipName->text());
        query.addBindValue(ui->EquipAmt->text());
        query.addBindValue(ui->EquipNo->text().toInt());
        query.exec();
        refreshTabelView();
    }
    if(i==4)
    {
        QString searchsentence = "select EquipName,EquipAmt from EquipInfo where EquipNo = ";
        searchsentence.append(ui->EquipNo->text());
        qDebug()<<"search_sen"<<searchsentence;
        query.exec(searchsentence);
        query.first();
        ui->EquipName->setText(query.value("EquipName").toString());
        ui->EquipAmt->setText(query.value("EquipAmt").toString());
    }
    qDebug()<<"Error:"<<query.lastError().text();
}
void EquipmentInfoDialog::refreshTabelView()
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
