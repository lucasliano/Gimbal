#include <QDebug>
#include <QSettings>
#include <QValidator>
#include <QMessageBox>
#include <QByteArray>
#include "interfaz.h"
#include "ui_interfaz.h"



#define PITCH 0
#define ROLL 1
#define YAW 2

#define LIMITE 55


Interfaz::Interfaz(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Interfaz)
    {
        //Inicialización
        ui->setupUi(this);
        roll = 0;
        pitch = 0;
        yaw = 0;
        ui->roll2->setValue(roll);
        ui->pitch1->setValue(pitch);

        //Inicialización de la comunicación
        Port = nullptr;    //indica que el objeto puerto no esta creado;
        Portname = "";
        EnumerarPuertos();
        HabilitarBotones(false);
        //HabilitarBotones(true);


    }

Interfaz::~Interfaz()
{
    delete Port;
    delete ui;
}

void Interfaz::on_noseup_clicked()
{
    //Cosas de la interfaz - Mateo
    if(pitch <= LIMITE)
    {
        pitch = pitch + 5;
        ui->impresion->setText("Moviste el gimbal hacia arriba");

    }else
    {
        pitch = (LIMITE+5);
    }
    ui->pitch1->setValue(pitch);
    //Cosas de la comunicacion

    QByteArray dato;
    dato.append(pitch+128);
    GenerarTrama(&dato , 0);
    EnviarDatos(dato);


}

void Interfaz::on_nosedown_clicked()
{
    //Cosas de la interfaz - Mateo
    if(pitch >= -LIMITE)
    {
        pitch = pitch - 5;
        ui->impresion->setText("Moviste el gimbal hacia abajo");

    }else
    {
        pitch = -(LIMITE+5);
    }

    ui->pitch1->setValue(pitch);
    //Cosas de la comunicacion
    QByteArray dato;
    dato.append(pitch+128);
    GenerarTrama(&dato , 0);
    EnviarDatos(dato);
}

void Interfaz::on_noseright_clicked()
{
    //Cosas de la interfaz - Mateo
    if(roll <= LIMITE)
    {
        roll = roll + 5;
        ui->impresion->setText("Moviste el gimbal hacia la derecha");

    }
    ui->roll2->setValue(roll);
    //Cosas de la comunicacion

    QByteArray dato;
    dato.append(roll+128);
    GenerarTrama(&dato , 1);
    EnviarDatos(dato);
}

void Interfaz::on_noseleft_clicked()
{
    //Cosas de la interfaz - Mateo
    if(roll >= -LIMITE)
    {
        roll = roll - 5;
        ui->impresion->setText("Moviste el gimbal hacia la izquierda");
        ui->roll2->setValue(roll);
    }
    ui->roll2->setValue(roll);
    //Cosas de la comunicacion

    QByteArray dato;
    dato.append(roll+128);
    GenerarTrama(&dato , 1);
    EnviarDatos(dato);
}

void Interfaz::on_modo1_clicked()
{
    ui->impresion->setText("Cambiaste al modo 1");
}

void Interfaz::on_modo2_clicked()
{
    ui->impresion->setText("Cambiaste al modo 2");
}

void Interfaz::on_calibrar_clicked()
{
    //Cosas de la interfaz - Mateo
    pitch=0;
    roll=0;
    yaw=0;
    ui->yaw->setValue(0);
    ui->roll2->setValue(0);//reseteo los valores a 0 cuando se aprieta calibrar
    ui->pitch1->setValue(0);

    //Cosas de la comunicacion
    QByteArray dato;
    dato.clear();
    dato.append(pitch+128);
    GenerarTrama(&dato,0);
    EnviarDatos(dato);

    dato.clear();
    dato.append(roll+128);
    GenerarTrama(&dato,0);
    EnviarDatos(dato);

    dato.clear();
    dato.append(yaw+128);
    GenerarTrama(&dato,0);
    EnviarDatos(dato);

}

void Interfaz::EnumerarPuertos()
{
    ui->comboBoxPort->clear();

    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();  //me devuelve una lista con los puertos que tengo

    if(ports.size() == 0)
    {
        QMessageBox::critical(this,"Error","No hay puertos disponibles!");
        //HabilitarBotones(false);

    }else{
        for (int i = 0; i < ports.size(); i++)
        {
            ui->comboBoxPort->addItem(ports.at(i).portName(), ports.at(i).portName());
        }
    }
}

void Interfaz::HabilitarBotones(bool info)
{
    ui->noseup->setEnabled(info);
    ui->nosedown->setEnabled(info);
    ui->noseleft->setEnabled(info);
    ui->noseright->setEnabled(info);
    ui->calibrar->setEnabled(info);
    ui->yaw->setEnabled(info);
    ui->pitch1->setEnabled(info);
    ui->roll2->setEnabled(info);
    ui->modo1->setEnabled(info);
    ui->modo2->setEnabled(info);
}

void Interfaz::on_pitch1_editingFinished()
{
    //Cosas de la interfaz - Mateo
    if(ui->pitch1->value() <= (LIMITE+5) && ui->pitch1->value() >= -(LIMITE+5))
    {
        pitch = (char) ui->pitch1->value();
        ui->impresion->setText("Moviste el gimbal en el pitch");
        QByteArray dato;
        dato.append(pitch+128);
        GenerarTrama(&dato,0);
        EnviarDatos(dato);
    }else {
        ui->pitch1->setValue(pitch);
    }
}

void Interfaz::on_roll2_editingFinished()
{
    //Cosas de la interfaz
    if(ui->roll2->value() <= (LIMITE+5) && ui->roll2->value() >= -(LIMITE+5))
    {
        roll = (char) ui->roll2->value();
        ui->impresion->setText("Moviste el gimbal en el roll");
        QByteArray dato;
        dato.append(roll+128);
        GenerarTrama(&dato,1);
        EnviarDatos(dato);
    }else {
        ui->roll2->setValue(roll);
    }
}

void Interfaz::on_yaw_valueChanged(const QString &arg1)
{
    if(ui->yaw->value() <= (LIMITE+5) && ui->yaw->value() >= -(LIMITE+5))
    {
        yaw = (char) ui->yaw->value();
        ui->impresion->setText("Moviste el gimbal en el yaw");
        QByteArray dato;
        dato.append(yaw+128);
        GenerarTrama(&dato,2);
        EnviarDatos(dato);

    }else {
        ui->yaw->setValue(yaw);
    }

}

void Interfaz::on_comboBoxPort_currentIndexChanged(int index)
{
    Portname = ui->comboBoxPort->itemData(index).toString();    //recupero la data del item de indice index
}

void Interfaz::on_btnUpdate_clicked()
{
    //Cosas de comunicacion
    Port = nullptr;    //indica que el objeto puerto no esta creado;
    Portname = "";
    EnumerarPuertos();
}

void Interfaz::EnviarDatos(QByteArray buff)
{

    if(Port)
    {
       qint64 i;
       i = Port->write(buff);

       qDebug() << i << buff;

       buff.clear();

       }
    else
    {
        QMessageBox::critical(this,"Error", QString::fromLatin1("Hay problemas con el envio de datos"));
        pitch = 0;
        roll = 0;
        yaw = 0;
        ui->yaw->setValue(0);
        ui->roll2->setValue(0);//reseteo los valores a 0 cuando se aprieta calibrar
        ui->pitch1->setValue(0);
    }
}

void Interfaz::GenerarTrama(QByteArray* buff, const int tipo)
{
    /**
    if(!buff->startsWith('-'))
    {
        buff->prepend('0');                             //Si no es negativo, le ponemos 0
        if(buff->length() == 2) buff->prepend('0');     //Si son solo 2 caracteres, le metemos otro
    }else {
        if(buff->length() == 2) buff->insert(1,'0');
    }
    **/
    switch (tipo)
    {
        case 0:
            buff->prepend("PIT");
            break;
        case 1:
            buff->prepend("RLL");
            break;
        case 2:
            buff->prepend("YAW");
            break;
        default:
            buff->prepend("@");
            break;
    }

    buff->prepend('#');
    buff->append("@");
}

void Interfaz::Recibiendo()
{
    QByteArray aux;
    aux.resize(int(Port->bytesAvailable()));
    aux = Port->readAll();
    aux.append('\0');
    QMessageBox::critical(this,"Error", aux);
}

void Interfaz::on_pushButtonConectar_clicked()
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
            QMessageBox::critical(this,"Error","No se puede abrir el puerto " + Port->portName());
            delete Port;
            Port = nullptr;
        }
        else
        {
            ui->statusBar->showMessage("Conectado", 1000);
            HabilitarBotones(true);
            ui->pushButtonConectar->setText("Desconectar");
            connect(Port,SIGNAL(readyRead()),this,SLOT(Recibiendo())); //quien y que manda,receptor y slot(una funcion)
        }
    }
    else
    {
        delete Port;
        Port = nullptr;
        ui->pushButtonConectar->setText("Conectar");
    }
}

void Interfaz::on_btnEnviar_clicked()
{
    //Cosas de la comunicacion
    QByteArray dato;
    QByteArray dato1;
    QByteArray dato2;

    dato.clear();
    dato1.clear();
    dato2.clear();


    dato.append(pitch+128);
    dato1.append(roll+128);
    dato2.append(yaw+128);

    GenerarTrama(&dato,PITCH);
    GenerarTrama(&dato1,ROLL);
    GenerarTrama(&dato2,YAW);

    EnviarDatos(dato);
    EnviarDatos(dato1);
    EnviarDatos(dato2);
}



void Interfaz::on_btnPlot_clicked()
{
    frmGrafico.show();
}
