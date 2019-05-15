#ifndef MEDICINEINFODIALOG_H
#define MEDICINEINFODIALOG_H

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
class MedicineInfoDialog;
}

class MedicineInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MedicineInfoDialog(QWidget *parent = nullptr);
    ~MedicineInfoDialog();

    QButtonGroup *LoginRadioBtnGroup;
    QRadioButton *add,*del,*change,*search;

public slots:
    void submit();
    void refreshTabelView();

private:
    Ui::MedicineInfoDialog *ui;
};

#endif // MEDICINEINFODIALOG_H
