#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "produit.h"
#include"offre.h"
#include <QMainWindow>
#include <QItemSelectionModel>
#include <QStandardItemModel>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QString>
#include <QDate>

#include <QMainWindow>

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
    void on_pushButton_pressed();

    void on_pushButton_released();

    void on_pushButton_2_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_2_pressed();

    void on_treeView_activated(const QModelIndex &index);

    void on_treeView_2_activated(const QModelIndex &index);

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_13_clicked();

    void on_treeView_offre_activated(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    produit pr ;
    offre of ;
};
#endif // MAINWINDOW_H
