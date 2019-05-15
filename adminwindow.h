#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include "logindialog.h"
#include <QString>
#include <QTimer>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QSqlQueryModel>
#include <iostream>
#include <QSqlRecord>
#include "connect_mysql.h"
#include "util.h"
#include "logindialog.h"
#include "stuinfodialog.h"
#include "equipmentinfodialog.h"
#include "gradedialog.h"
#include "medicineinfodialog.h"
#include "stulogininfodialog.h"
#include "teacherinfodialog.h"
#include "teacherlogininfodialog.h"
#include "teachinginfodialog.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);
    ~AdminWindow();

    //QButtonGroup *LoginRadioBtnGroup;
    //QRadioButton *add,*del,*change,*search;
public slots:
    int updateNo();
    void selectStuInfo();
    void selectStuLoginInfo();
    void selectTeaInfo();
    void selectTeaLoginInfo();
    void selectMedicinInfo();
    void selectEquipmentInfo();
    void selectTeachingInfo();
    void selectGrade();

    void comboxChange();

    void tiaozhuan();
    int modeSelect();
    //void refreshTableView();
private:
    Ui::AdminWindow *ui;
    //StuInfoDialog stuinfodia;
};

#endif // ADMINWINDOW_H
