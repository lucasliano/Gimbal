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
#include <QtWidgets/QPushButton>
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
    QPushButton *btnScreen;

    void setupUi(QWidget *Plotting)
    {
        if (Plotting->objectName().isEmpty())
            Plotting->setObjectName(QString::fromUtf8("Plotting"));
        Plotting->resize(1037, 720);
        centralWidget = new QWidget(Plotting);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setGeometry(QRect(10, 10, 991, 691));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        customPlot = new QCustomPlot(centralWidget);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));

        verticalLayout->addWidget(customPlot);

        btnScreen = new QPushButton(Plotting);
        btnScreen->setObjectName(QString::fromUtf8("btnScreen"));
        btnScreen->setGeometry(QRect(1004, 0, 31, 261));

        retranslateUi(Plotting);

        QMetaObject::connectSlotsByName(Plotting);
    } // setupUi

    void retranslateUi(QWidget *Plotting)
    {
        Plotting->setWindowTitle(QApplication::translate("Plotting", "Form", nullptr));
        btnScreen->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Plotting: public Ui_Plotting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTTING_H
