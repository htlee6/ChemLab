#ifndef TEACHERINFODIALOG_H
#define TEACHERINFODIALOG_H

#include <QDialog>
#include <QButtonGroup>
#include <QRadioButton>
#include <QMainWindow>
#include <QString>
#include <QTimer>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include "connect_mysql.h"
#include "util.h"

namespace Ui {
class TeacherInfoDialog;
}

class TeacherInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TeacherInfoDialog(QWidget *parent = nullptr);
    ~TeacherInfoDialog();

    QButtonGroup *LoginRadioBtnGroup;
    QRadioButton *add,*del,*change,*search;
public slots:
    void submit();
    void refreshTabelView();
private:
    Ui::TeacherInfoDialog *ui;
};

#endif // TEACHERINFODIALOG_H
