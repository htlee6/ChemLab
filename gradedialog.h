#ifndef GRADEDIALOG_H
#define GRADEDIALOG_H

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
class GradeDialog;
}

class GradeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GradeDialog(QWidget *parent = nullptr);
    ~GradeDialog();

    QButtonGroup *LoginRadioBtnGroup;
    QRadioButton *add,*del,*change,*search;

private:
    Ui::GradeDialog *ui;

public slots:
    void submit();
    void refreshTabelView();
};

#endif // GRADEDIALOG_H
