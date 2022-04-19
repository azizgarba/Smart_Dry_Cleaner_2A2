#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"materiel.h"
#include "excel.h"

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

   void on_valider_clicked();

    void on_supprimer_clicked();



    void on_modifier_clicked();

    void on_afficher_clicked();

    void on_ecricherche_textChanged(const QString &arg1);







    void on_insererim_clicked();

    void on_afficherexcel_clicked();

    void on_historique_clicked();

    void on_affmate_activated(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
     materiel mtmp;

};
#endif // MAINWINDOW_H
