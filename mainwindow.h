#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employee.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_ajouter_clicked();

    void on_pushButton_ajouter_pressed();

    void on_pushButton_ajouter_released();

    void on_pushButton_modif_clicked();

    void on_pushButton_modif_pressed();

    void on_pushButton_modif_released();

    void on_pushButton_supp_clicked();

    void on_pushButton_supp_pressed();

    void on_pushButton_supp_released();

private:
    Ui::MainWindow *ui;
    Employee etmp;
};
#endif // MAINWINDOW_H
