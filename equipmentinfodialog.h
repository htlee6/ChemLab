#ifndef EQUIPMENTINFODIALOG_H
#define EQUIPMENTINFODIALOG_H

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
class EquipmentInfoDialog;
}

class EquipmentInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EquipmentInfoDialog(QWidget *parent = nullptr);
    ~EquipmentInfoDialog();

    QButtonGroup *LoginRadioBtnGroup;
    QRadioButton *add,*del,*change,*search;
public slots:
    void submit();
    void refreshTabelView();
private:
    Ui::EquipmentInfoDialog *ui;
};

#endif // EQUIPMENTINFODIALOG_H
