/********************************************************************************
** Form generated from reading UI file 'interfaz.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFAZ_H
#define UI_INTERFAZ_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Interfaz
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QPushButton *noseup;
    QPushButton *noseright;
    QPushButton *nosedown;
    QPushButton *noseleft;
    QGroupBox *groupBox_2;
    QRadioButton *modo1;
    QRadioButton *modo2;
    QPushButton *calibrar;
    QPushButton *btnEnviar;
    QGroupBox *groupBox_4;
    QGroupBox *groupBox_5;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QSpinBox *yaw;
    QSpinBox *pitch1;
    QSpinBox *roll2;
    QGroupBox *groupBox_6;
    QLabel *label_5;
    QProgressBar *bateria;
    QLabel *impresion;
    QGroupBox *groupBox_3;
    QComboBox *comboBoxPort;
    QPushButton *pushButtonConectar;
    QPushButton *btnUpdate;
    QMenuBar *menuBar;
    QMenu *menuInterfaz;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Interfaz)
    {
        if (Interfaz->objectName().isEmpty())
            Interfaz->setObjectName(QString::fromUtf8("Interfaz"));
        Interfaz->resize(678, 471);
        Interfaz->setDocumentMode(false);
        centralWidget = new QWidget(Interfaz);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 281, 311));
        noseup = new QPushButton(groupBox);
        noseup->setObjectName(QString::fromUtf8("noseup"));
        noseup->setGeometry(QRect(100, 30, 81, 81));
        noseright = new QPushButton(groupBox);
        noseright->setObjectName(QString::fromUtf8("noseright"));
        noseright->setGeometry(QRect(180, 110, 81, 81));
        nosedown = new QPushButton(groupBox);
        nosedown->setObjectName(QString::fromUtf8("nosedown"));
        nosedown->setGeometry(QRect(100, 190, 81, 81));
        noseleft = new QPushButton(groupBox);
        noseleft->setObjectName(QString::fromUtf8("noseleft"));
        noseleft->setGeometry(QRect(20, 110, 81, 81));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(290, 10, 181, 311));
        modo1 = new QRadioButton(groupBox_2);
        modo1->setObjectName(QString::fromUtf8("modo1"));
        modo1->setGeometry(QRect(50, 50, 82, 17));
        modo2 = new QRadioButton(groupBox_2);
        modo2->setObjectName(QString::fromUtf8("modo2"));
        modo2->setGeometry(QRect(50, 80, 82, 17));
        calibrar = new QPushButton(groupBox_2);
        calibrar->setObjectName(QString::fromUtf8("calibrar"));
        calibrar->setGeometry(QRect(50, 140, 75, 23));
        btnEnviar = new QPushButton(groupBox_2);
        btnEnviar->setObjectName(QString::fromUtf8("btnEnviar"));
        btnEnviar->setGeometry(QRect(50, 200, 75, 23));
        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(470, 10, 191, 311));
        groupBox_5 = new QGroupBox(groupBox_4);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(20, 20, 151, 191));
        label_2 = new QLabel(groupBox_5);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(60, 20, 47, 13));
        label_3 = new QLabel(groupBox_5);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(60, 70, 47, 13));
        label_4 = new QLabel(groupBox_5);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(60, 120, 47, 13));
        yaw = new QSpinBox(groupBox_5);
        yaw->setObjectName(QString::fromUtf8("yaw"));
        yaw->setGeometry(QRect(20, 140, 111, 21));
        yaw->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        yaw->setMinimum(-45);
        yaw->setMaximum(45);
        yaw->setSingleStep(5);
        pitch1 = new QSpinBox(groupBox_5);
        pitch1->setObjectName(QString::fromUtf8("pitch1"));
        pitch1->setGeometry(QRect(20, 40, 111, 21));
        pitch1->setToolTipDuration(-1);
        pitch1->setButtonSymbols(QAbstractSpinBox::NoButtons);
        pitch1->setMinimum(-99999);
        pitch1->setMaximum(99999);
        pitch1->setSingleStep(5);
        pitch1->setStepType(QAbstractSpinBox::DefaultStepType);
        pitch1->setValue(0);
        roll2 = new QSpinBox(groupBox_5);
        roll2->setObjectName(QString::fromUtf8("roll2"));
        roll2->setGeometry(QRect(20, 90, 111, 21));
        roll2->setButtonSymbols(QAbstractSpinBox::NoButtons);
        roll2->setMinimum(-99999);
        roll2->setMaximum(99999);
        groupBox_6 = new QGroupBox(groupBox_4);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(20, 210, 151, 81));
        label_5 = new QLabel(groupBox_6);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(40, 20, 71, 16));
        bateria = new QProgressBar(groupBox_6);
        bateria->setObjectName(QString::fromUtf8("bateria"));
        bateria->setGeometry(QRect(20, 40, 118, 23));
        bateria->setValue(100);
        impresion = new QLabel(centralWidget);
        impresion->setObjectName(QString::fromUtf8("impresion"));
        impresion->setGeometry(QRect(10, 330, 271, 61));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(290, 320, 371, 80));
        comboBoxPort = new QComboBox(groupBox_3);
        comboBoxPort->setObjectName(QString::fromUtf8("comboBoxPort"));
        comboBoxPort->setGeometry(QRect(20, 30, 184, 23));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBoxPort->sizePolicy().hasHeightForWidth());
        comboBoxPort->setSizePolicy(sizePolicy);
        comboBoxPort->setMaximumSize(QSize(16777215, 16777215));
        comboBoxPort->setMaxVisibleItems(4);
        pushButtonConectar = new QPushButton(groupBox_3);
        pushButtonConectar->setObjectName(QString::fromUtf8("pushButtonConectar"));
        pushButtonConectar->setGeometry(QRect(250, 50, 111, 23));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButtonConectar->sizePolicy().hasHeightForWidth());
        pushButtonConectar->setSizePolicy(sizePolicy1);
        btnUpdate = new QPushButton(groupBox_3);
        btnUpdate->setObjectName(QString::fromUtf8("btnUpdate"));
        btnUpdate->setGeometry(QRect(250, 10, 111, 23));
        sizePolicy1.setHeightForWidth(btnUpdate->sizePolicy().hasHeightForWidth());
        btnUpdate->setSizePolicy(sizePolicy1);
        Interfaz->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Interfaz);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 678, 21));
        menuInterfaz = new QMenu(menuBar);
        menuInterfaz->setObjectName(QString::fromUtf8("menuInterfaz"));
        Interfaz->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Interfaz);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setEnabled(true);
        mainToolBar->setMovable(true);
        mainToolBar->setFloatable(true);
        Interfaz->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Interfaz);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Interfaz->setStatusBar(statusBar);

        menuBar->addAction(menuInterfaz->menuAction());

        retranslateUi(Interfaz);

        comboBoxPort->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(Interfaz);
    } // setupUi

    void retranslateUi(QMainWindow *Interfaz)
    {
        Interfaz->setWindowTitle(QApplication::translate("Interfaz", "Interfaz", nullptr));
        groupBox->setTitle(QApplication::translate("Interfaz", "Controls", nullptr));
        noseup->setText(QApplication::translate("Interfaz", "Nose Up", nullptr));
        noseright->setText(QApplication::translate("Interfaz", "Nose Right", nullptr));
        nosedown->setText(QApplication::translate("Interfaz", "Nose Down", nullptr));
        noseleft->setText(QApplication::translate("Interfaz", "Nose Left", nullptr));
        groupBox_2->setTitle(QApplication::translate("Interfaz", "Advanced Control", nullptr));
        modo1->setText(QApplication::translate("Interfaz", "Mode 1", nullptr));
        modo2->setText(QApplication::translate("Interfaz", "Mode 2", nullptr));
        calibrar->setText(QApplication::translate("Interfaz", "Calibrate", nullptr));
        btnEnviar->setText(QApplication::translate("Interfaz", "Enviar Datos", nullptr));
        groupBox_4->setTitle(QApplication::translate("Interfaz", "Datos", nullptr));
        groupBox_5->setTitle(QApplication::translate("Interfaz", "Euler angles", nullptr));
        label_2->setText(QApplication::translate("Interfaz", "PITCH", nullptr));
        label_3->setText(QApplication::translate("Interfaz", "ROLL", nullptr));
        label_4->setText(QApplication::translate("Interfaz", "YAW", nullptr));
        groupBox_6->setTitle(QApplication::translate("Interfaz", "Extra-Info", nullptr));
        label_5->setText(QApplication::translate("Interfaz", "Battery power", nullptr));
        impresion->setText(QString());
        groupBox_3->setTitle(QApplication::translate("Interfaz", "Comunicaci\303\263n", nullptr));
        pushButtonConectar->setText(QApplication::translate("Interfaz", "Conectar", nullptr));
        btnUpdate->setText(QApplication::translate("Interfaz", "Actualizar Puertos", nullptr));
        menuInterfaz->setTitle(QApplication::translate("Interfaz", "Principal", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Interfaz: public Ui_Interfaz {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFAZ_H
