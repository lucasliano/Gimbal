/********************************************************************************
** Form generated from reading UI file 'bienvenidos.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BIENVENIDOS_H
#define UI_BIENVENIDOS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_bienvenidos
{
public:
    QPushButton *pushButton;
    QLabel *label;

    void setupUi(QDialog *bienvenidos)
    {
        if (bienvenidos->objectName().isEmpty())
            bienvenidos->setObjectName(QString::fromUtf8("bienvenidos"));
        bienvenidos->resize(458, 317);
        pushButton = new QPushButton(bienvenidos);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(140, 190, 151, 51));
        label = new QLabel(bienvenidos);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 30, 371, 141));

        retranslateUi(bienvenidos);

        QMetaObject::connectSlotsByName(bienvenidos);
    } // setupUi

    void retranslateUi(QDialog *bienvenidos)
    {
        bienvenidos->setWindowTitle(QApplication::translate("bienvenidos", "Dialog", nullptr));
        pushButton->setText(QApplication::translate("bienvenidos", "Presione para continuar", nullptr));
        label->setText(QApplication::translate("bienvenidos", "<html><head/><body><p><span style=\" font-size:48pt; color:#ff0000;\">Bienvenidos</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class bienvenidos: public Ui_bienvenidos {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BIENVENIDOS_H
