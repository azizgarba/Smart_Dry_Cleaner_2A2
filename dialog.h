#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "employee.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_ajouter_clicked();

private:
    Ui::Dialog *ui;
    Employee etmp;
};

#endif // DIALOG_H
