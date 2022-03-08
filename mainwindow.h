#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fournisseur.h"
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
    void on_pb_ajouter_clicked();

    void on_le_aff_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_supprimer_pressed();

    void on_pb_supprimer_released();

    void on_pb_ajouter_pressed();

    void on_pb_ajouter_released();

    void on_pb_modifier_clicked();

    void on_tab_fournisseurs_activated(const QModelIndex &index);

    void on_pb_tri_activated(const QString &arg1);

private:
    Ui::MainWindow *ui;
    Fournisseur ftmp;

};
#endif // MAINWINDOW_H
