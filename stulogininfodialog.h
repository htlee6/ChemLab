#ifndef STULOGININFODIALOG_H
#define STULOGININFODIALOG_H

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
class StuLoginInfoDialog;
}

class StuLoginInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StuLoginInfoDialog(QWidget *parent = nullptr);
    ~StuLoginInfoDialog();

    QButtonGroup *LoginRadioBtnGroup;
    QRadioButton *add,*del,*change,*search;

public slots:
    void submit();
    void refreshTabelView();

private:
    Ui::StuLoginInfoDialog *ui;
};

#endif // STULOGININFODIALOG_H
