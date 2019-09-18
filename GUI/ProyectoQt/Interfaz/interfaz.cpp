#include <QSettings>
#include <QValidator>
#include <QMessageBox>
#include <QByteArray>
#include "comserie.h"
#include "interfaz.h"
#include "ui_interfaz.h"

#include <QDebug>

Interfaz::Interfaz(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Interfaz)
    {
        //Cosas de interfaz
        ui->setupUi(this);
        roll = 0;
        pitch = 0;
        ui->roll2->setValue(roll);
        ui->pitch1->setValue(pitch);

        //Cosas de comunicacion
        Port = nullptr;    //indica que el objeto puerto no esta creado;
        Portname = "";
        EnumerarPuertos();
        //HabilitarBotones(false);
        HabilitarBotones(true);
    }

Interfaz::~Interfaz()
{
    delete Port;
    delete ui;
}

void Interfaz::on_noseup_clicked()
{ 
    //Cosas de la interfaz - Mateo
    if(pitch <= 44)
    {
        pitch = pitch + 5;
        ui->impresion->setText("Moviste el gimbal hacia arriba");
        ui->pitch1->setValue(pitch);
    }

    //Cosas de la comunicacion
    //QString dato;
    QByteArray dato;
    dato.setNum(pitch);
    GenerarTrama(&dato , 0);
    EnviarDatos(dato);

}

void Interfaz::on_nosedown_clicked()
{
    //Cosas de la interfaz - Mateo
    if(pitch >= -44)
    {
        pitch = pitch - 5;
        ui->impresion->setText("Moviste el gimbal hacia abajo");
        ui->pitch1->setValue(pitch);
    }

    //Cosas de la comunicacion


}

void Interfaz::on_noseright_clicked()
{    
    //Cosas de la interfaz - Mateo
    if(roll <= 44)
    {
        roll = roll + 5;
        ui->impresion->setText("Moviste el gimbal hacia la derecha");
        ui->roll2->setValue(roll);
    }

    //Cosas de la comunicacion

}

void Interfaz::on_noseleft_clicked()
{
    //Cosas de la interfaz - Mateo
    if(roll >= -40)
    {
        roll = roll - 5;
        ui->impresion->setText("Moviste el gimbal hacia la izquierda");
        ui->roll2->setValue(roll);
    }

    //Cosas de la comunicacion


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
    ui->yaw->setValue(0);
    ui->roll2->setValue(0);//reseteo los valores a 0 cuando se aprieta calibrar
    ui->pitch1->setValue(0);

    //Cosas de la comunicacion
    QByteArray dato;
    dato.setNum(pitch);
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
    if(ui->pitch1->value() <= 44 && ui->pitch1->value() >= -44)
    {
        pitch = ui->pitch1->value();
        ui->impresion->setText("Moviste el gimbal en el pitch");
    }else {
        ui->pitch1->setValue(pitch);
    }
}

void Interfaz::on_roll2_editingFinished()
{
    //Cosas de la interfaz - Mateo
    if(ui->roll2->value() <= 44 && ui->roll2->value() >= -44)
    {
        roll = ui->roll2->value();
        ui->impresion->setText("Moviste el gimbal en el roll");
    }else {
        ui->roll2->setValue(roll);
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
   // QMessageBox::critical(this,"recibi esto de la trama",buff);

    if(Port)
    {
       qint64 i;
       i = Port->write(buff);

       qDebug() << i << buff;

       //QByteArray numero;
       //numero.setNum(i);
       //QMessageBox::critical(this,"bytes enviados",numero);

       buff.clear();

       }
    else
    {
        QMessageBox::critical(this,"Error", QString::fromLatin1("Hay problemas con el envio de datos"));
    }
}

void Interfaz::GenerarTrama(QByteArray* buff, const int tipo)
{



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
            //QMessageBox::critical(this,"Error",Port->portName());
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

    dato.setNum(pitch);
    dato1.setNum(roll);

    GenerarTrama(&dato,0);
    GenerarTrama(&dato1,1);


    EnviarDatos(dato);
    EnviarDatos(dato1);

}
