#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "arduino.h"

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


    void update_nb();

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

    void on_recherche_textChanged(const QString &arg1);

    void on_pushButton_4_clicked();

    void on_pdf_aff_clicked();

    void on_pushButton_clicked();

private:
    QByteArray data; // variable contenant les données reçues

        Arduino A; // objet temporaire
    Ui::MainWindow *ui;
    Fournisseur ftmp;

};
#endif // MAINWINDOW_H
