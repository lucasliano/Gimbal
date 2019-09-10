#include "interfaz.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include "bienvenidos.h"
#include "interfaz.h"
#include "comserie.h"
int pitch;
int roll;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap("Splash.jpeg"));
    splash->show();

    Interfaz w;
    QTimer::singleShot(5000,splash,SLOT(close()));//Muestro la foto del gimbal
    QTimer::singleShot(5000,&w,SLOT(show()));
    //w.show();




    return a.exec();
}
