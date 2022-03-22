#ifndef GEMPLOYEE_H
#define GEMPLOYEE_H

#include <QDialog>

namespace Ui {
class GEmployee;
}

class GEmployee : public QDialog
{
    Q_OBJECT

public:
    explicit GEmployee(QWidget *parent = nullptr);
    ~GEmployee();

private:
    Ui::GEmployee *ui;
};

#endif // GEMPLOYEE_H

