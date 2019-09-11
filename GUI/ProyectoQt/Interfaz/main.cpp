#include "interfaz.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include "bienvenidos.h"
#include "interfaz.h"
#include "comserie.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Esto de acá inicializa la imagen que va a saltar
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap("img/inicio.jpeg"));
    splash->show(); //Se muestra la imagen

    Interfaz w; //Inicializo la ventana "interfaz"

    //Lanzo dos timers para que se muestre la imagen de inicio y dsps inicie la ventana.

    QTimer::singleShot(2500,splash,SLOT(close()));//Muestro la foto del gimbal
    QTimer::singleShot(2500,&w,SLOT(show()));




    return a.exec();
}
