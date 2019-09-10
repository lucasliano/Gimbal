#ifndef INTERFAZ_H
#define INTERFAZ_H
#include <QMainWindow>
#include "comserie.h"
namespace Ui {
class Interfaz;
}

class Interfaz : public QMainWindow
{
    Q_OBJECT

public:
    explicit Interfaz(QWidget *parent = nullptr);
    ~Interfaz();

private slots:
    void on_noseup_clicked();

    void on_noseright_clicked();

    void on_nosedown_clicked();

    void on_noseleft_clicked();

    void on_modo1_clicked();

    void on_modo2_clicked();

    void on_calibrar_clicked();

    void on_bateria_valueChanged(int value);

private:
    Ui::Interfaz *ui;

};

#endif // INTERFAZ_H
