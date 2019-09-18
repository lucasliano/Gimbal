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

    void on_pitch1_editingFinished();

    void on_roll2_editingFinished();

    void on_pushButtonConectar_clicked();

    void on_comboBoxPort_currentIndexChanged(int index);

    void on_btnUpdate_clicked();

    void Recibiendo();

    void on_btnEnviar_clicked();

private:
    Ui::Interfaz *ui;
    QString Portname;
    QSerialPort *Port;
    int pitch;
    int roll;
    void EnumerarPuertos();
    void HabilitarBotones(bool);
    void EnviarDatos(QByteArray);
    void GenerarTrama(QByteArray*,const int);

};

#endif // INTERFAZ_H
