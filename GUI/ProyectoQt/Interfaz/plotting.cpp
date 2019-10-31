#include "plotting.h"
#include "ui_plotting.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>

Plotting::Plotting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Plotting)
{
    //Esto incializa el objeto del gráfico
    ui->setupUi(this);
    ui->verticalLayout->addWidget(ui->customPlot);
    setupRealtimeDataDemo(ui->customPlot);
    setWindowTitle("Angulos de Euler");
    ui->customPlot->replot();
}

Plotting::Plotting(QWidget *parent, double p, double r, double y):
    QWidget(parent),
    ui(new Ui::Plotting)
{
    //Esto incializa el objeto del gráfico
    ui->setupUi(this);
    ui->verticalLayout->addWidget(ui->customPlot);
    setupRealtimeDataDemo(ui->customPlot);
    setWindowTitle("Angulos de Euler");
    ui->customPlot->replot();
    pitch = p;
    qDebug() << pitch;
    roll = r;
    yaw = y;
}

Plotting::~Plotting()
{
    delete ui;
}


void Plotting::setupRealtimeDataDemo(QCustomPlot *customPlot)
{
  // include this section to fully disable antialiasing for higher performance:
  /*
  customPlot->setNotAntialiasedElements(QCP::aeAll);
  QFont font;
  font.setStyleStrategy(QFont::NoAntialias);
  customPlot->xAxis->setTickLabelFont(font);
  customPlot->yAxis->setTickLabelFont(font);
  customPlot->legend->setFont(font);
  */
  //Inicializamos las lineas
  //PITCH
  customPlot->addGraph(); // blue line
  customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
  //ROLL
  customPlot->addGraph(); // orange line
  customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));
  //YAW
  customPlot->addGraph(); // purple line
  customPlot->graph(2)->setPen(QPen(QColor(245, 15, 215)));

  QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
  timeTicker->setTimeFormat("%h:%m:%s");
  customPlot->xAxis->setTicker(timeTicker);
  customPlot->axisRect()->setupFullAxesBox();
  customPlot->yAxis->setRange(-90, 90);         //Acá se actualiza cuanto se muestra del gráfico

  // make left and bottom axes transfer their ranges to right and top axes:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

  // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
  connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
  dataTimer.start(0); // Interval 0 means to refresh as fast as possible
}

void Plotting::screenShot()
{
    QPixmap pm = ui->customPlot->toPixmap(this->frameGeometry().width()-4,this->frameGeometry().height()-4,1);
    QString fileName = "Screenshot.png";
    pm.save("./screenshots/"+fileName,"PNG");
}

void Plotting::realtimeDataSlot()
{
  static QTime time(QTime::currentTime());
  // calculate two new data points:
  double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
  static double lastPointKey = 0;

  /**
  if (key-lastPointKey > 0.002) // at most add point every 2 ms
  {
    // add data to lines:
    ui->customPlot->graph(0)->addData(key, qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
    ui->customPlot->graph(1)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
    // rescale value (vertical) axis to fit the current data:
    //ui->customPlot->graph(0)->rescaleValueAxis();
    //ui->customPlot->graph(1)->rescaleValueAxis(true);
    lastPointKey = key;
  }
  **/
  if (key-lastPointKey > 0.002) // at most add point every 2 ms
  {
      //Pitch
      ui->customPlot->graph(0)->addData(key, pitch);
      //ui->customPlot->graph(0)->rescaleValueAxis();
      //Roll
      ui->customPlot->graph(1)->addData(key, roll);
      //ui->customPlot->graph(1)->rescaleValueAxis();
      //Yaw
      ui->customPlot->graph(2)->addData(key, yaw);
      //ui->customPlot->graph(2)->rescaleValueAxis();
  }

  // make key axis range scroll with the data (at a constant range size of 8):
  ui->customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
  ui->customPlot->replot();

  // calculate frames per second:
  static double lastFpsKey;
  static int frameCount;
  ++frameCount;
  if (key-lastFpsKey > 2) // average fps over 2 seconds
  {
    lastFpsKey = key;
    frameCount = 0;
  }

}

void Plotting::on_btnScreen_clicked()
{
    screenShot();
}
