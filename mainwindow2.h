#ifndef MAINWINDOW2_H
#define MAINWINDOW2_H

#include <QMainWindow>
#include "employee.h"
#include"produit.h"
#include"offre.h"


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

    void on_pushButton_8_clicked();

    void on_pushButton_13_clicked();

    void on_tableView_3_activated(const QModelIndex &index);

    void on_pushButton_12_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_5_clicked();

    void on_treeView_activated(const QModelIndex &index);

    void on_treeView_2_activated(const QModelIndex &index);

    void on_pushButton_15_clicked();

    void on_lineEdit_search_2_textChanged(const QString &arg1);

    void on_pb_ajouter_clicked();

    void on_le_aff_clicked();

public slots:
    void openDialog();

private:
    Ui::MainWindow2 *ui;
    Employee etmp;
    produit pr;
    offre of;
    //Dialog *Dialog;
};

#endif // MAINWINDOW2_H
