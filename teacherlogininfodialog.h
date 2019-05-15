#ifndef TEACHERLOGININFODIALOG_H
#define TEACHERLOGININFODIALOG_H

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
class TeacherLoginInfoDialog;
}

class TeacherLoginInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TeacherLoginInfoDialog(QWidget *parent = nullptr);
    ~TeacherLoginInfoDialog();

    QButtonGroup *LoginRadioBtnGroup;
    QRadioButton *add,*del,*change,*search;

public slots:
    void submit();
    void refreshTabelView();

private:
    Ui::TeacherLoginInfoDialog *ui;
};

#endif // TEACHERLOGININFODIALOG_H
