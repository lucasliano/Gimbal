/********************************************************************************
** Form generated from reading UI file 'comserie.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMSERIE_H
#define UI_COMSERIE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_comserie
{
public:
    QComboBox *comboBoxPort;
    QLabel *label;
    QPlainTextEdit *plainTextEditRX;
    QPlainTextEdit *plainTextEditTX;
    QPushButton *pushButtonEnviar;
    QLabel *label_2;
    QPushButton *pushButtonConectar;

    void setupUi(QDialog *comserie)
    {
        if (comserie->objectName().isEmpty())
            comserie->setObjectName(QString::fromUtf8("comserie"));
        comserie->resize(587, 454);
        comserie->setAutoFillBackground(false);
        comboBoxPort = new QComboBox(comserie);
        comboBoxPort->setObjectName(QString::fromUtf8("comboBoxPort"));
        comboBoxPort->setGeometry(QRect(10, 10, 184, 23));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBoxPort->sizePolicy().hasHeightForWidth());
        comboBoxPort->setSizePolicy(sizePolicy);
        comboBoxPort->setMaximumSize(QSize(16777215, 16777215));
        comboBoxPort->setMaxVisibleItems(4);
        label = new QLabel(comserie);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, -30, 13, 157));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        plainTextEditRX = new QPlainTextEdit(comserie);
        plainTextEditRX->setObjectName(QString::fromUtf8("plainTextEditRX"));
        plainTextEditRX->setGeometry(QRect(10, 60, 346, 157));
        plainTextEditTX = new QPlainTextEdit(comserie);
        plainTextEditTX->setObjectName(QString::fromUtf8("plainTextEditTX"));
        plainTextEditTX->setGeometry(QRect(10, 250, 265, 157));
        pushButtonEnviar = new QPushButton(comserie);
        pushButtonEnviar->setObjectName(QString::fromUtf8("pushButtonEnviar"));
        pushButtonEnviar->setEnabled(true);
        pushButtonEnviar->setGeometry(QRect(280, 380, 75, 23));
        label_2 = new QLabel(comserie);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 160, 13, 157));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        pushButtonConectar = new QPushButton(comserie);
        pushButtonConectar->setObjectName(QString::fromUtf8("pushButtonConectar"));
        pushButtonConectar->setGeometry(QRect(200, 10, 75, 23));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButtonConectar->sizePolicy().hasHeightForWidth());
        pushButtonConectar->setSizePolicy(sizePolicy2);

        retranslateUi(comserie);

        comboBoxPort->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(comserie);
    } // setupUi

    void retranslateUi(QDialog *comserie)
    {
        comserie->setWindowTitle(QApplication::translate("comserie", "Dialog", nullptr));
        label->setText(QApplication::translate("comserie", "RX", nullptr));
        plainTextEditRX->setPlainText(QString());
        plainTextEditTX->setPlainText(QString());
        pushButtonEnviar->setText(QApplication::translate("comserie", "Enviar", nullptr));
        label_2->setText(QApplication::translate("comserie", "TX", nullptr));
        pushButtonConectar->setText(QApplication::translate("comserie", "Conectar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class comserie: public Ui_comserie {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMSERIE_H
