/********************************************************************************
** Form generated from reading UI file 'plotting.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTTING_H
#define UI_PLOTTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_Plotting
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QCustomPlot *customPlot;

    void setupUi(QWidget *Plotting)
    {
        if (Plotting->objectName().isEmpty())
            Plotting->setObjectName(QString::fromUtf8("Plotting"));
        Plotting->resize(1024, 720);
        centralWidget = new QWidget(Plotting);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setGeometry(QRect(10, 10, 991, 691));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        customPlot = new QCustomPlot(centralWidget);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));

        verticalLayout->addWidget(customPlot);


        retranslateUi(Plotting);

        QMetaObject::connectSlotsByName(Plotting);
    } // setupUi

    void retranslateUi(QWidget *Plotting)
    {
        Plotting->setWindowTitle(QApplication::translate("Plotting", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Plotting: public Ui_Plotting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTTING_H
