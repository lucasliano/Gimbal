#ifndef PLOTTING_H
#define PLOTTING_H

#include <QWidget>
#include "qcustomplot.h"

namespace Ui {
class Plotting;
}

class Plotting : public QWidget
{
    Q_OBJECT

public:
    explicit Plotting(QWidget *parent = nullptr);
    Plotting(QWidget *parent = nullptr, double p = 0, double r = 0, double y = 0);
    void setupRealtimeDataDemo(QCustomPlot *customPlot);

    ~Plotting();

private slots:
    void realtimeDataSlot();
    void screenShot();

    void on_btnScreen_clicked();

private:
    Ui::Plotting *ui;
    //QCustomPlot* customPlot;
//    double pitch;
//    double roll;
//    double yaw;

    //Esto es del ejemplo
    QString demoName;
    QTimer dataTimer;
    QCPItemTracer *itemDemoPhaseTracer;
};

#endif // PLOTTING_H
