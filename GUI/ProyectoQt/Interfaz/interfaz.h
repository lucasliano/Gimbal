#ifndef INTERFAZ_H
#define INTERFAZ_H
#include <QMainWindow>
#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "plotting.h"

#define BUFFERSIZE 50

namespace Ui {
class Interfaz;
}

class Interfaz : public QMainWindow
{
    Q_OBJECT

public:
    explicit Interfaz(QWidget *parent = nullptr);
    Plotting *frmGrafico;
//    double pitch = 0;
//    double roll = 0;
//    double yaw = 0;
    char bufferRx[BUFFERSIZE];
    ~Interfaz();

private slots:
    void on_noseup_clicked();

    void on_noseright_clicked();

    void on_nosedown_clicked();

    void on_noseleft_clicked();

    void on_calibrar_clicked();

    void on_pitch1_editingFinished();

    void on_roll2_editingFinished();

    void on_pushButtonConectar_clicked();

    void on_comboBoxPort_currentIndexChanged(int index);

    void on_btnUpdate_clicked();

    void Recibiendo();

    void on_btnEnviar_clicked();

    void on_yaw_valueChanged(const QString &arg1);

    void on_btnPlot_clicked();

    void verificarTrama(void);



private:
    Ui::Interfaz *ui;
    QString Portname;
    QSerialPort *Port;
    QTimer Timer;

    char setpointPitch;
    char setpointRoll;
    char setpointYaw;


    void EnumerarPuertos();
    void HabilitarBotones(bool);
    void EnviarDatos(QByteArray);
    void GenerarTrama(QByteArray*,const int);
    void AnalizarTrama(QByteArray buff);

};

#endif // INTERFAZ_H
