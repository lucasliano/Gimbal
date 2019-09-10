/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QComboBox *comboBoxPort;
    QPushButton *pushButtonConectar;
    QLabel *label;
    QLabel *label_2;
    QPlainTextEdit *plainTextEditTX;
    QPushButton *pushButtonEnviar;
    QPlainTextEdit *plainTextEditRX;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->resize(383, 367);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(383, 367));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        comboBoxPort = new QComboBox(centralWidget);
        comboBoxPort->setObjectName(QString::fromUtf8("comboBoxPort"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBoxPort->sizePolicy().hasHeightForWidth());
        comboBoxPort->setSizePolicy(sizePolicy1);
        comboBoxPort->setMaximumSize(QSize(16777215, 16777215));
        comboBoxPort->setMaxVisibleItems(4);

        gridLayout->addWidget(comboBoxPort, 0, 2, 1, 1);

        pushButtonConectar = new QPushButton(centralWidget);
        pushButtonConectar->setObjectName(QString::fromUtf8("pushButtonConectar"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButtonConectar->sizePolicy().hasHeightForWidth());
        pushButtonConectar->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(pushButtonConectar, 0, 3, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(label, 2, 0, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy3.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(label_2, 4, 0, 1, 1);

        plainTextEditTX = new QPlainTextEdit(centralWidget);
        plainTextEditTX->setObjectName(QString::fromUtf8("plainTextEditTX"));

        gridLayout->addWidget(plainTextEditTX, 4, 2, 1, 2);

        pushButtonEnviar = new QPushButton(centralWidget);
        pushButtonEnviar->setObjectName(QString::fromUtf8("pushButtonEnviar"));
        pushButtonEnviar->setEnabled(true);

        gridLayout->addWidget(pushButtonEnviar, 4, 4, 1, 1);

        plainTextEditRX = new QPlainTextEdit(centralWidget);
        plainTextEditRX->setObjectName(QString::fromUtf8("plainTextEditRX"));

        gridLayout->addWidget(plainTextEditRX, 2, 2, 1, 3);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        comboBoxPort->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Serial Terminal", nullptr));
        pushButtonConectar->setText(QApplication::translate("MainWindow", "Conectar", nullptr));
        label->setText(QApplication::translate("MainWindow", "RX", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "TX", nullptr));
        plainTextEditTX->setPlainText(QString());
        pushButtonEnviar->setText(QApplication::translate("MainWindow", "Enviar", nullptr));
        plainTextEditRX->setPlainText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
