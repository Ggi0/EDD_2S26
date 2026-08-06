/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QFrame *frame;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *txt_id;
    QLineEdit *txt_nombre;
    QLineEdit *txt_genero;
    QPushButton *btt_agregarArtista;
    QFrame *frame_2;
    QLabel *label_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(240, 10, 291, 71));
        QFont font;
        font.setPointSize(50);
        label->setFont(font);
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(40, 100, 311, 411));
        frame->setStyleSheet(QString::fromUtf8("Background: rgb(79, 143, 0)"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 10, 291, 71));
        QFont font1;
        font1.setPointSize(40);
        label_2->setFont(font1);
        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 80, 51, 51));
        QFont font2;
        font2.setPointSize(25);
        font2.setBold(true);
        font2.setItalic(true);
        label_4->setFont(font2);
        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(30, 170, 121, 51));
        label_5->setFont(font2);
        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 260, 211, 51));
        label_6->setFont(font2);
        txt_id = new QLineEdit(frame);
        txt_id->setObjectName(QString::fromUtf8("txt_id"));
        txt_id->setGeometry(QRect(40, 130, 151, 31));
        txt_id->setStyleSheet(QString::fromUtf8("background:rgb(146, 146, 146)"));
        txt_nombre = new QLineEdit(frame);
        txt_nombre->setObjectName(QString::fromUtf8("txt_nombre"));
        txt_nombre->setGeometry(QRect(50, 220, 151, 31));
        txt_nombre->setStyleSheet(QString::fromUtf8("background:rgb(146, 146, 146)"));
        txt_genero = new QLineEdit(frame);
        txt_genero->setObjectName(QString::fromUtf8("txt_genero"));
        txt_genero->setGeometry(QRect(50, 320, 151, 31));
        txt_genero->setStyleSheet(QString::fromUtf8("background:rgb(146, 146, 146)"));
        btt_agregarArtista = new QPushButton(frame);
        btt_agregarArtista->setObjectName(QString::fromUtf8("btt_agregarArtista"));
        btt_agregarArtista->setGeometry(QRect(190, 370, 100, 32));
        btt_agregarArtista->setStyleSheet(QString::fromUtf8("Background: rgb(148, 23, 81)"));
        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(440, 100, 301, 411));
        frame_2->setStyleSheet(QString::fromUtf8("Background: rgb(79, 143, 0)"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 10, 291, 71));
        label_3->setFont(font1);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Reproductor:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Agregar Artista:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "ID:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Nombre:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Genero musical:", nullptr));
        txt_id->setText(QString());
        txt_nombre->setText(QString());
        txt_genero->setText(QString());
        btt_agregarArtista->setText(QCoreApplication::translate("MainWindow", "Agregar", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Cantantes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
