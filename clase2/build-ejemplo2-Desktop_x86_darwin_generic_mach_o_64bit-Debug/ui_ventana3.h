/********************************************************************************
** Form generated from reading UI file 'ventana3.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VENTANA3_H
#define UI_VENTANA3_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ventana3
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *btt_regresar;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ventana3)
    {
        if (ventana3->objectName().isEmpty())
            ventana3->setObjectName(QString::fromUtf8("ventana3"));
        ventana3->resize(800, 600);
        centralwidget = new QWidget(ventana3);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(250, 70, 271, 111));
        QFont font;
        font.setPointSize(50);
        label->setFont(font);
        btt_regresar = new QPushButton(centralwidget);
        btt_regresar->setObjectName(QString::fromUtf8("btt_regresar"));
        btt_regresar->setGeometry(QRect(270, 440, 161, 51));
        ventana3->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ventana3);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        ventana3->setMenuBar(menubar);
        statusbar = new QStatusBar(ventana3);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ventana3->setStatusBar(statusbar);

        retranslateUi(ventana3);

        QMetaObject::connectSlotsByName(ventana3);
    } // setupUi

    void retranslateUi(QMainWindow *ventana3)
    {
        ventana3->setWindowTitle(QCoreApplication::translate("ventana3", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("ventana3", "ventana 3", nullptr));
        btt_regresar->setText(QCoreApplication::translate("ventana3", "Regresar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ventana3: public Ui_ventana3 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VENTANA3_H
