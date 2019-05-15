#include "stuwindow.h"
#include "ui_stuwindow.h"

#include "logindialog.h"
#include <QString>
#include "util.h"
#include "connect_mysql.h"
#include <QFileDialog>
#include <QTimer>



StuWindow::StuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StuWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),ui->refreshBtn,SLOT(click()));
    timer->setSingleShot(true);
    timer->start(1000);
    //qDebug()<<"stuno"<<stuno;
    //ui->acclabel->setText(QString::number(stuno));
    connect(ui->refreshBtn,SIGNAL(clicked()),this,SLOT(updateNo()));
    connect(ui->uploadButton,SIGNAL(clicked()),this,SLOT(uploadData()));
    //connect(ui->ExpSelectComboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(changeExpPDF()));

    QByteArray cameraDevice = QCamera::availableDevices()[0];

    camera = new QCamera(cameraDevice);
    QHBoxLayout* layout = new QHBoxLayout;
    viewfinder = new QCameraViewfinder(this);
    viewfinder->resize(640,480);

    QVBoxLayout* vLayout = new QVBoxLayout ;
    recordButton = ui->record;
    pauseButton = ui->pause;
    stopButton = ui->stop;
    exitButton = ui->exit;


    connect(recordButton, SIGNAL(clicked()), this, SLOT(recordVideo()));
    connect(pauseButton,SIGNAL(clicked()),this, SLOT(pause()));
    connect(stopButton,SIGNAL(clicked()), this,SLOT(stop()));
    connect(exitButton,SIGNAL(clicked()), this, SLOT(close()));

    layout->addWidget(viewfinder);
    layout->addLayout(vLayout);


    camera->setViewfinder(viewfinder);
    camera->setCaptureMode(QCamera::CaptureVideo);
    camera->start();

    mediaRecorder = new QMediaRecorder(camera);
    connect(mediaRecorder, SIGNAL(durationChanged(qint64)), this, SLOT(changeDuration(qint64)));
    setLayout(layout);
}

StuWindow::~StuWindow()
{
    delete ui;
}

void StuWindow::updateNo()
{
    int stuNo = readAcc();
    QSqlDatabase db = connect_mysql("");
    QSqlQuery query(db);
    QString sentence ="select StuName from StuInfo where StuNo = ";
    sentence.append(QString::number(stuNo));
    query.exec(sentence);
    query.first();
    QString name = query.value("StuName").toString();
    ui->acclabel->setText(QString::number(stuNo));
    ui->namelabel->setText(name);
}

void StuWindow:: recordVideo()
{
    qDebug() << "record video";
    mediaRecorder->setOutputLocation(QUrl("/Users/Lihaotian/Desktop"));
    mediaRecorder->record();
    ui->RecordStatus->setText("录像中");
}

void StuWindow:: changeDuration(qint64 seconds)
{
    qDebug() << seconds;
    //QString str = QString("Recorded %1 sec").arg(seconds);
    timeDisplay->setNum(int(seconds));

}

void StuWindow::pause()
{
    qDebug() << "pause";
    mediaRecorder->pause();
    ui->RecordStatus->setText("已暂停");
}

void StuWindow::stop()
{
    mediaRecorder->stop();
    ui->RecordStatus->setText("已结束");
    qDebug()<<"文件路径"<<mediaRecorder->actualLocation();
    QString video_location=mediaRecorder->actualLocation().toString();

    QString stuno = QString::number(readAcc(), 10);
    //qDebug()<<"StuNo is "<<stuno;
    QString expindex = QString::number(ui->ExpSelectComboBox->currentIndex()+1,10);
    //qDebug()<<"expindex is "<<expindex;
    QString datapkgno = stuno.append(expindex);

    QSqlDatabase dbtest = connect_mysql("");
    QSqlQuery querytest(dbtest);
    QString testsentence = "select count(*) from DataPkg where DataPkgNo = ";
    testsentence.append(datapkgno);
    querytest.exec(testsentence);
    querytest.first();
    int count = querytest.value("count(*)").toInt();
    //qDebug()<<"Count:"<<count;
    if(count > 0)
    {
        QString changesentence = "update DataPkg set VideoNo=? where DataPkgNo=?";
        QSqlDatabase db = connect_mysql("");
        QSqlQuery query(db);
        query.prepare(changesentence);
        query.addBindValue(video_location);
        query.addBindValue(datapkgno);
        query.exec();
    }
    if(count == 0)
    {
        //qDebug()<<"Count小于0";
        QString insertsentence = "insert into DataPkg(DataPkgNo,VideoNo) values (:DataPkgNo,:VideoNo)";
        QSqlDatabase db = connect_mysql("");
        QSqlQuery query(db);
        query.prepare(insertsentence);
        query.bindValue(":DataPkgNo",datapkgno);
        query.bindValue(":VideoNo",video_location);
        query.exec();
    }

}

void StuWindow::uploadData()
{
    QSqlDatabase db = connect_mysql("");
    QSqlQuery query(db);
    QString filename = QFileDialog::getOpenFileName(NULL,NULL,"/",NULL,NULL,NULL);
    qDebug()<<"filename is "<<filename;

    QString stuno = QString::number(readAcc(), 10);
    //qDebug()<<"StuNo is "<<stuno;
    QString expindex = QString::number(ui->ExpSelectComboBox->currentIndex()+1,10);
    //qDebug()<<"expindex is "<<expindex;
    QString datapkgno = stuno.append(expindex);

    QSqlDatabase dbtest = connect_mysql("");
    QSqlQuery querytest(dbtest);
    QString testsentence = "select count(*) from DataPkg where DataPkgNo = ";
    testsentence.append(datapkgno);
    querytest.exec(testsentence);
    querytest.first();
    int count = querytest.value("count(*)").toInt();
    qDebug()<<"Count:"<<count;
    if(count > 0)
    {
        QString changesentence = "update DataPkg set Data=? where DataPkgNo=?";
        QSqlDatabase db = connect_mysql("");
        QSqlQuery query(db);
        query.prepare(changesentence);
        query.addBindValue(filename);
        query.addBindValue(datapkgno);
        query.exec();
    }
    if(count == 0)
    {
        //qDebug()<<"Count小于0";
        QString insertsentence = "insert into DataPkg(DataPkgNo,Data) values (:DataPkgNo,:Data)";
        QSqlDatabase db = connect_mysql("");
        QSqlQuery query(db);
        query.prepare(insertsentence);
        query.bindValue(":DataPkgNo",datapkgno);
        query.bindValue(":Data",filename);
        query.exec();
    }
}

