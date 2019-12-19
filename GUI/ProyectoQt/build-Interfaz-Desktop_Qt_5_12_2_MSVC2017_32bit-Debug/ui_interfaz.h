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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Interfaz
{
public:
    QAction *actionPlotting_Angles;
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QPushButton *noseup;
    QPushButton *noseright;
    QPushButton *nosedown;
    QPushButton *noseleft;
    QGroupBox *groupBox_2;
    QGroupBox *groupBox_7;
    QTextBrowser *txtConsola;
    QSpinBox *txt_kp;
    QSpinBox *txt_kd;
    QSpinBox *txt_ki;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *btnPID;
    QGroupBox *groupBox_4;
    QGroupBox *groupBox_5;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QSpinBox *yaw;
    QSpinBox *pitch1;
    QSpinBox *roll2;
    QPushButton *btnEnviar;
    QPushButton *calibrar;
    QGroupBox *groupBox_3;
    QComboBox *comboBoxPort;
    QPushButton *pushButtonConectar;
    QPushButton *btnUpdate;
    QPushButton *btnPlot;
    QMenuBar *menuBar;
    QMenu *menuInterfaz;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Interfaz)
    {
        if (Interfaz->objectName().isEmpty())
            Interfaz->setObjectName(QString::fromUtf8("Interfaz"));
        Interfaz->resize(673, 459);
        Interfaz->setDocumentMode(false);
        actionPlotting_Angles = new QAction(Interfaz);
        actionPlotting_Angles->setObjectName(QString::fromUtf8("actionPlotting_Angles"));
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
        groupBox_2->setGeometry(QRect(290, 10, 181, 391));
        groupBox_7 = new QGroupBox(groupBox_2);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(10, 190, 161, 191));
        txtConsola = new QTextBrowser(groupBox_7);
        txtConsola->setObjectName(QString::fromUtf8("txtConsola"));
        txtConsola->setEnabled(true);
        txtConsola->setGeometry(QRect(10, 20, 141, 161));
        txtConsola->setReadOnly(true);
        txtConsola->setTextInteractionFlags(Qt::LinksAccessibleByKeyboard|Qt::LinksAccessibleByMouse|Qt::TextBrowserInteraction|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        txt_kp = new QSpinBox(groupBox_2);
        txt_kp->setObjectName(QString::fromUtf8("txt_kp"));
        txt_kp->setGeometry(QRect(90, 30, 51, 21));
        txt_kp->setToolTipDuration(-1);
        txt_kp->setButtonSymbols(QAbstractSpinBox::NoButtons);
        txt_kp->setMinimum(-99999);
        txt_kp->setMaximum(99999);
        txt_kp->setSingleStep(5);
        txt_kp->setStepType(QAbstractSpinBox::DefaultStepType);
        txt_kp->setValue(0);
        txt_kd = new QSpinBox(groupBox_2);
        txt_kd->setObjectName(QString::fromUtf8("txt_kd"));
        txt_kd->setGeometry(QRect(90, 60, 51, 21));
        txt_kd->setToolTipDuration(-1);
        txt_kd->setButtonSymbols(QAbstractSpinBox::NoButtons);
        txt_kd->setMinimum(-99999);
        txt_kd->setMaximum(99999);
        txt_kd->setSingleStep(5);
        txt_kd->setStepType(QAbstractSpinBox::DefaultStepType);
        txt_kd->setValue(0);
        txt_ki = new QSpinBox(groupBox_2);
        txt_ki->setObjectName(QString::fromUtf8("txt_ki"));
        txt_ki->setGeometry(QRect(90, 90, 51, 21));
        txt_ki->setToolTipDuration(-1);
        txt_ki->setButtonSymbols(QAbstractSpinBox::NoButtons);
        txt_ki->setMinimum(-99999);
        txt_ki->setMaximum(99999);
        txt_ki->setSingleStep(5);
        txt_ki->setStepType(QAbstractSpinBox::DefaultStepType);
        txt_ki->setValue(0);
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(30, 20, 31, 31));
        QFont font;
        font.setPointSize(14);
        font.setBold(false);
        font.setWeight(50);
        label_5->setFont(font);
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(30, 50, 31, 31));
        label_6->setFont(font);
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(30, 80, 21, 31));
        label_7->setFont(font);
        btnPID = new QPushButton(groupBox_2);
        btnPID->setObjectName(QString::fromUtf8("btnPID"));
        btnPID->setGeometry(QRect(10, 120, 161, 51));
        QFont font1;
        font1.setPointSize(12);
        btnPID->setFont(font1);
        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(470, 10, 191, 311));
        groupBox_5 = new QGroupBox(groupBox_4);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(20, 20, 151, 271));
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
        btnEnviar = new QPushButton(groupBox_5);
        btnEnviar->setObjectName(QString::fromUtf8("btnEnviar"));
        btnEnviar->setGeometry(QRect(10, 170, 131, 41));
        btnEnviar->setFont(font1);
        calibrar = new QPushButton(groupBox_5);
        calibrar->setObjectName(QString::fromUtf8("calibrar"));
        calibrar->setGeometry(QRect(10, 220, 131, 41));
        calibrar->setFont(font1);
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 319, 281, 81));
        comboBoxPort = new QComboBox(groupBox_3);
        comboBoxPort->setObjectName(QString::fromUtf8("comboBoxPort"));
        comboBoxPort->setGeometry(QRect(20, 30, 121, 23));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBoxPort->sizePolicy().hasHeightForWidth());
        comboBoxPort->setSizePolicy(sizePolicy);
        comboBoxPort->setMaximumSize(QSize(16777215, 16777215));
        comboBoxPort->setMaxVisibleItems(4);
        pushButtonConectar = new QPushButton(groupBox_3);
        pushButtonConectar->setObjectName(QString::fromUtf8("pushButtonConectar"));
        pushButtonConectar->setGeometry(QRect(160, 50, 111, 23));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButtonConectar->sizePolicy().hasHeightForWidth());
        pushButtonConectar->setSizePolicy(sizePolicy1);
        btnUpdate = new QPushButton(groupBox_3);
        btnUpdate->setObjectName(QString::fromUtf8("btnUpdate"));
        btnUpdate->setGeometry(QRect(160, 10, 111, 23));
        sizePolicy1.setHeightForWidth(btnUpdate->sizePolicy().hasHeightForWidth());
        btnUpdate->setSizePolicy(sizePolicy1);
        btnPlot = new QPushButton(centralWidget);
        btnPlot->setObjectName(QString::fromUtf8("btnPlot"));
        btnPlot->setGeometry(QRect(480, 320, 181, 81));
        QFont font2;
        font2.setPointSize(20);
        btnPlot->setFont(font2);
        Interfaz->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Interfaz);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 673, 21));
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
        actionPlotting_Angles->setText(QApplication::translate("Interfaz", "Plotting Angles", nullptr));
        groupBox->setTitle(QApplication::translate("Interfaz", "Controles", nullptr));
        noseup->setText(QApplication::translate("Interfaz", "Pitch Up", nullptr));
        noseright->setText(QApplication::translate("Interfaz", "Roll Right", nullptr));
        nosedown->setText(QApplication::translate("Interfaz", "Pitch Down", nullptr));
        noseleft->setText(QApplication::translate("Interfaz", "Roll Left", nullptr));
        groupBox_2->setTitle(QApplication::translate("Interfaz", "Controles Avanzados", nullptr));
        groupBox_7->setTitle(QApplication::translate("Interfaz", "Consola", nullptr));
        label_5->setText(QApplication::translate("Interfaz", "Kp", nullptr));
        label_6->setText(QApplication::translate("Interfaz", "Kd", nullptr));
        label_7->setText(QApplication::translate("Interfaz", "Ki", nullptr));
        btnPID->setText(QApplication::translate("Interfaz", "Actualizar PID", nullptr));
        groupBox_4->setTitle(QApplication::translate("Interfaz", "Datos", nullptr));
        groupBox_5->setTitle(QApplication::translate("Interfaz", "\303\201ngulos de Euler", nullptr));
        label_2->setText(QApplication::translate("Interfaz", "PITCH", nullptr));
        label_3->setText(QApplication::translate("Interfaz", "ROLL", nullptr));
        label_4->setText(QApplication::translate("Interfaz", "YAW", nullptr));
        btnEnviar->setText(QApplication::translate("Interfaz", "Enviar Datos", nullptr));
        calibrar->setText(QApplication::translate("Interfaz", "Calibrate", nullptr));
        groupBox_3->setTitle(QApplication::translate("Interfaz", "Comunicaci\303\263n", nullptr));
        pushButtonConectar->setText(QApplication::translate("Interfaz", "Conectar", nullptr));
        btnUpdate->setText(QApplication::translate("Interfaz", "Actualizar Puertos", nullptr));
        btnPlot->setText(QApplication::translate("Interfaz", "Graficar", nullptr));
        menuInterfaz->setTitle(QApplication::translate("Interfaz", "Principal", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Interfaz: public Ui_Interfaz {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFAZ_H
