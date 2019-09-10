#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QByteArray>
#include <stdlib.h>
#include <windows.h>


int tamano = 0;
char auxiliar[2];
int i = 0;
char *datos;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);  //inicializo interfaz

    Port = NULL;        //indica que el objeto puerto no esta creado;
    Portname = "";
    EnumerarPuertos();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete Port;
}

void MainWindow::EnumerarPuertos()
{
    ui->comboBoxPort->clear();

    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();  //me devuelve una lista con los puertos que tengo

    for (int i = 0; i < ports.size(); i++)
    {
        ui->comboBoxPort->addItem(ports.at(i).portName(), ports.at(i).portName());
    }
}

void MainWindow::on_pushButtonConectar_clicked()
{
    if (!Port) //distinto de nulo
    {
        Port = new QSerialPort(Portname);
        Port->setBaudRate(QSerialPort::Baud9600); //velocidad
        Port->setFlowControl(QSerialPort::NoFlowControl);
        Port->setParity(QSerialPort::NoParity);
        Port->setDataBits(QSerialPort::Data8);
        Port->setStopBits(QSerialPort::OneStop);
        if(!Port->open(QIODevice::ReadWrite))
        {
            QMessageBox::critical(this,"Error","No se puede abrir el puerto "+Port->portName());
            delete Port;
            Port = NULL;
        }
        else
        {
            ui->pushButtonConectar->setText("Desconectar");
            connect(Port,SIGNAL(readyRead()),this,SLOT(on_Port_rx())); //quien y que manda,receptor y slot(una funcion)
        }
    }
    else
    {
        delete Port;
        Port = NULL;
        ui->pushButtonConectar->setText("Conectar");
    }
}

void MainWindow::on_pushButtonEnviar_clicked()
{
    if(Port)
    {
        QByteArray aux;

        aux.append(ui->plainTextEditTX->toPlainText());
        datos = aux.data();


        while((*datos) != '\0')
        {
            QByteArray auxiliar;
            auxiliar.append((*datos));
            auxiliar.append('\0');

            Port->write(auxiliar);
            QMessageBox::information(this,"Enviando",QString::fromLatin1(""));
            datos = datos + 1;

        }


        ui->plainTextEditTX->clear();
    }
    else
    {
        QMessageBox::critical(this,"Error",QString::fromLatin1("No hay ningun puerto abierto"));
    }
}

void MainWindow::on_Port_rx()
{
    QByteArray aux;
    aux.resize(Port->bytesAvailable());
    //Port->read(aux.data(),aux.size());
    aux=Port->readAll();
    //aux.append('\0');
    ui->plainTextEditRX->appendPlainText(aux);
}

void MainWindow::on_comboBoxPort_currentIndexChanged(int index)
{
    Portname = ui->comboBoxPort->itemData(index).toString();    //recupero la data del item de indice index
}
