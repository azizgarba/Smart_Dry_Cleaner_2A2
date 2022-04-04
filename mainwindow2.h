#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <QMainWindow>
#include "employee.h"
#include "dialog.h"
#include "widget.h"

namespace Ui {
class MainWindow2;
}

class MainWindow2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow2(QWidget *parent = nullptr);
    ~MainWindow2();

private slots:
    void on_pushButton_ajouter_clicked();

    void on_pushButton_modif_clicked();

    void on_pushButton_qr_clicked();

    void on_pushButton_supp_clicked();

    void on_pushButton_excel_clicked();

    void on_pushButton_trier_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_ajouter_pressed();

    void on_pushButton_ajouter_released();

    void on_pushButton_modif_pressed();

    void on_pushButton_modif_released();

    void on_pushButton_qr_pressed();

    void on_pushButton_qr_released();

    void on_pushButton_supp_pressed();

    void on_pushButton_supp_released();

    void on_pushButton_excel_pressed();

    void on_pushButton_excel_released();

    void on_pushButton_chat_pressed();

    void on_pushButton_chat_released();

    void on_pushButton_trier_pressed();

    void on_pushButton_trier_released();

    void on_pushButton_chat_clicked();

public slots:
    void openDialog();

private:
    Ui::MainWindow2 *ui;
    Employee etmp;
    Dialog *Dialog;
};

#endif // MAINWINDOW2_H
