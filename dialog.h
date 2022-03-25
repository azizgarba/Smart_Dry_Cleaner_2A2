//metier chat
#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

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
    void on_chat_pressed();

    void on_chat_released();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
