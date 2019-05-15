#ifndef STUINFODIALOG_H
#define STUINFODIALOG_H

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
class StuInfoDialog;
}

class StuInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StuInfoDialog(QWidget *parent = nullptr);
    ~StuInfoDialog();

    QButtonGroup *LoginRadioBtnGroup;
    QRadioButton *add,*del,*change,*search;

public slots:
    void submit();
    void refreshTabelView();

private:
    Ui::StuInfoDialog *ui;
};

#endif // STUINFODIALOG_H
