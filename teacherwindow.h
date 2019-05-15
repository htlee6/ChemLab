#ifndef TEACHERWINDOW_H
#define TEACHERWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
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
#include "ratingdialog.h"

namespace Ui {
class TeacherWindow;
}

class TeacherWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TeacherWindow(QWidget *parent = nullptr);
    ~TeacherWindow();
    RatingDialog rate;
public slots:
    int updateNo();
    void selectStuInfo();
    void chooseStu();
    void ShowFileDir();
    void ShowRatingDialog();
private:
    Ui::TeacherWindow *ui;
};

#endif // TEACHERWINDOW_H
