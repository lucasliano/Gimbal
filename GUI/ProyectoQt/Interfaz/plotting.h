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

    void setupRealtimeDataDemo(QCustomPlot *customPlot);

    ~Plotting();

private slots:
    void realtimeDataSlot();
    void screenShot();

private:
    Ui::Plotting *ui;
    //QCustomPlot* customPlot;

    //Esto es del ejemplo
    QString demoName;
    QTimer dataTimer;
    QCPItemTracer *itemDemoPhaseTracer;
};

#endif // PLOTTING_H
