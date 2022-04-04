#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class widget;
}


class QTcpSocket;
namespace DuarteCorporation{

class widget : public QWidget
{
    Q_OBJECT

public:
    explicit widget(QWidget *parent = nullptr);
    ~widget();

private slots:
    void on_send_clicked();

    void on_bind_clicked();

private:
    Ui::widget *ui;
    QTcpSocket *nSocket;
};
}
#endif // WIDGET_H
