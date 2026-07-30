/********************************************************************************
** Form generated from reading UI file 'ventana2.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VENTANA2_H
#define UI_VENTANA2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ventana2
{
public:
    QFrame *ventana_reportes;
    QLabel *label;
    QLabel *lbl_image;

    void setupUi(QWidget *ventana2)
    {
        if (ventana2->objectName().isEmpty())
            ventana2->setObjectName(QString::fromUtf8("ventana2"));
        ventana2->resize(845, 613);
        ventana_reportes = new QFrame(ventana2);
        ventana_reportes->setObjectName(QString::fromUtf8("ventana_reportes"));
        ventana_reportes->setGeometry(QRect(30, 30, 751, 541));
        ventana_reportes->setStyleSheet(QString::fromUtf8("background: rgb(94, 94, 94)"));
        ventana_reportes->setFrameShape(QFrame::StyledPanel);
        ventana_reportes->setFrameShadow(QFrame::Raised);
        label = new QLabel(ventana_reportes);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(280, 20, 181, 51));
        QFont font;
        font.setPointSize(40);
        label->setFont(font);
        lbl_image = new QLabel(ventana_reportes);
        lbl_image->setObjectName(QString::fromUtf8("lbl_image"));
        lbl_image->setGeometry(QRect(110, 100, 561, 361));

        retranslateUi(ventana2);

        QMetaObject::connectSlotsByName(ventana2);
    } // setupUi

    void retranslateUi(QWidget *ventana2)
    {
        ventana2->setWindowTitle(QCoreApplication::translate("ventana2", "Form", nullptr));
        label->setText(QCoreApplication::translate("ventana2", "Reportes:", nullptr));
        lbl_image->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ventana2: public Ui_ventana2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VENTANA2_H
