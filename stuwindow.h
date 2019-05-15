#ifndef STUWINDOW_H
#define STUWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
//#include <QAxWidget>
#include "logindialog.h"
#include<QtMultimedia/QCamera>
#include<QtMultimediaWidgets/QCameraViewfinder>
#include<QtMultimedia/QMediaRecorder>


namespace Ui {
class StuWindow;
}

class StuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StuWindow(QWidget *parent = nullptr);
    ~StuWindow();

    //QAxWidget *officeContent_;
    //QLineEdit *received_acc;
    //int stuNo;
    QCamera* camera;
    QCameraViewfinder* viewfinder;
    QMediaRecorder* mediaRecorder;
    QPushButton* recordButton ;
    QPushButton* pauseButton ;
    QPushButton* stopButton;
    QPushButton* exitButton;
    QLabel* timeDisplay;


public slots:
    //void receiveStuNo();
    //void pressBtn();
    void updateNo();
    //void readStuNoFromLoginDialog();
    //void changeExpPDF();
    void uploadData();
    //void OpenPdf(QString &filedir);
    //void CloseOffice();
    void recordVideo();
    void changeDuration(qint64 seconds);
    void pause();
    void stop();


private:
    Ui::StuWindow *ui;
    //LoginDialog *logindialog;
};

#endif // STUWINDOW_H

