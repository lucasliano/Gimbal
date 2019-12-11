#include "plotting.h"
#include "ui_plotting.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>

extern double pitch;
extern double roll;
extern double yaw;
extern double out;


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
}

Plotting::~Plotting()
{
    delete ui;
}


void Plotting::setupRealtimeDataDemo(QCustomPlot *customPlot)
{
    customPlot->setLocale(QLocale(QLocale::Spanish, QLocale::LatinAmerica)); // period as decimal separator and comma as thousand separator
    customPlot->legend->setVisible(true);
    QFont legendFont = font();  // start out with MainWindow's font..
    legendFont.setPointSize(9); // and make a bit smaller for legend
    customPlot->legend->setFont(legendFont);
    customPlot->legend->setBrush(QBrush(QColor(255,255,255,230)));
    // by default, the legend is in the inset layout of the main axis rect. So this is how we access it to change legend placement:
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);


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
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    customPlot->graph(0)->setBrush(QBrush(QPixmap("./balboa.jpg"))); // fill with texture of specified image
//    customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
//    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    customPlot->graph(0)->setName("Pitch");
    //ROLL
    customPlot->addGraph();
    customPlot->graph(1)->setPen(QPen(QColor(0, 255, 0)));
    customPlot->graph(1)->setBrush(QBrush(QPixmap("./balboa.jpg"))); // fill with texture of specified image
//    customPlot->graph(1)->setLineStyle(QCPGraph::lsLine);
//    customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    customPlot->graph(1)->setName("Roll");
    //YAW
    customPlot->addGraph();
    customPlot->graph(2)->setPen(QPen(QColor(245, 15, 215)));
    customPlot->graph(2)->setBrush(QBrush(QPixmap("./balboa.jpg"))); // fill with texture of specified image
//    customPlot->graph(2)->setLineStyle(QCPGraph::lsLine);
//    customPlot->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    customPlot->graph(2)->setName("Yaw");
    //Referencia
    customPlot->addGraph();
    QPen blueDotPen;
    blueDotPen.setColor(QColor(255, 0, 0));
    blueDotPen.setStyle(Qt::DotLine);
    blueDotPen.setWidthF(3);
    customPlot->graph(3)->setPen(blueDotPen);
    customPlot->graph(3)->setName("Ref.");



    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    customPlot->xAxis->setTicker(timeTicker);
    customPlot->axisRect()->setupFullAxesBox();
    customPlot->yAxis->setRange(-90, 90);         //Acá se actualiza cuanto se muestra del gráfico


    // add title layout element:
    customPlot->plotLayout()->insertRow(0);
    customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(customPlot, "Angulos de Euler y Salida de Control", QFont("sans", 12, QFont::Bold)));
    // set labels:
    customPlot->xAxis->setLabel("Tiempo");
    customPlot->yAxis->setLabel("Ángulos [grados]");

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
      ui->customPlot->graph(3)->addData(key, out);
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
