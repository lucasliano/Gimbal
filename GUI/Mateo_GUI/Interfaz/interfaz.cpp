#include "interfaz.h"
#include "ui_interfaz.h"
#include <QSettings>
#include <QValidator>
#include "comserie.h"
extern int pitch;
extern int roll;
Interfaz::Interfaz(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Interfaz)
{
    ui->setupUi(this);
}

Interfaz::~Interfaz()
{
    delete ui;
}


void Interfaz::on_noseup_clicked()
{

    ui->impresion->setText("Moviste el gimbal hacia arriba");

     if(pitch<=44)//Pongo el valor maximo de pitch y si pasa ese valor vuelve a -180
         pitch=pitch+5;
   //ui->pitch1->setText(QString::number(pitch));  Lo cambie por un qspinbox
    ui->pitch1->setValue(pitch);

}
void Interfaz::on_nosedown_clicked()
{
    ui->impresion->setText("Moviste el gimbal hacia abajo");
  // ui->pitch1->setText(QString::number(pitch)); no funciona
    if(pitch>=-44)
       pitch=pitch-5;
   ui->pitch1->setValue(pitch);
}
void Interfaz::on_noseright_clicked()
{
    ui->impresion->setText("Moviste el gimbal hacia la derecha");

    if(roll<=44)
     roll=roll+5;
   //ui->roll1->setText(QString::number(roll));
    ui->roll2->setValue(roll);
}
void Interfaz::on_noseleft_clicked()
{
    ui->impresion->setText("Moviste el gimbal hacia la izquierda");

   //ui->roll1->setText(QString::number(roll));
     if(roll>=-44)
        roll=roll-5;
    ui->roll2->setValue(roll);

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
    pitch=0;
    //ui->pitch1->setText(QString::number(pitch));
    roll=0;
    //ui->roll1->setText(QString::number(pitch));
    ui->yaw->setValue(0);
    ui->roll2->setValue(0);//reseteo los valores a 0 cuando se aprieta calibrar
    ui->pitch1->setValue(0);
}


