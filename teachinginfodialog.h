#ifndef TEACHINGINFODIALOG_H
#define TEACHINGINFODIALOG_H

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
class TeachingInfoDialog;
}

class TeachingInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TeachingInfoDialog(QWidget *parent = nullptr);
    ~TeachingInfoDialog();

    QButtonGroup *LoginRadioBtnGroup;
    QRadioButton *add,*del,*change,*search;
private:
    Ui::TeachingInfoDialog *ui;
public slots:
    void submit();
    void refreshTabelView();

};

#endif // TEACHINGINFODIALOG_H
