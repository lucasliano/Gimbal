#ifndef COMSERIE_H
#define COMSERIE_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "interfaz.h"
namespace Ui {
class comserie;
}

class comserie : public QDialog
{
    Q_OBJECT

public:
    explicit comserie(QWidget *parent = nullptr);
    ~comserie();

private:
    Ui::comserie *ui;

private slots:
    void on_comboBoxPort_currentIndexChanged(int index);
    void on_pushButtonEnviar_clicked();
    void on_pushButtonConectar_clicked();
    void on_Port_rx();

    void on_comserie_finished(int result);


private:
    QString Portname;
    //QextSerialPort *Port;
    QSerialPort *Port;
    void EnumerarPuertos();
};



#endif // COMSERIE_H
