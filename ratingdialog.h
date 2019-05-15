#ifndef RATINGDIALOG_H
#define RATINGDIALOG_H

#include <QDialog>

namespace Ui {
class RatingDialog;
}

class RatingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RatingDialog(QWidget *parent = nullptr);
    ~RatingDialog();

public slots:
    void Rate();

    void ReceiveStuNo();
    void ReceiveExpNo();

private:
    Ui::RatingDialog *ui;
};

#endif // RATINGDIALOG_H
