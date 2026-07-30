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
    QFrame *frame;
    QLabel *label;
    QLineEdit *txt_id;
    QLineEdit *txt_nombre;
    QLineEdit *txt_anio;
    QLineEdit *txt_genero;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *btt_agregarPEli;
    QPushButton *btt_verReporte;
    QPushButton *btt_verReporte_2;
    QPushButton *btt_ejemplo;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 761, 531));
        QFont font;
        font.setBold(true);
        font.setItalic(false);
        frame->setFont(font);
        frame->setCursor(QCursor(Qt::UpArrowCursor));
        frame->setStyleSheet(QString::fromUtf8("background: qlineargradient(    spread: pad,    x1: 0, y1: 0,    x2: 1, y2: 0,    stop: 0 rgb(107, 108, 108),    stop: 1 rgb(123, 124, 124));"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(260, 30, 261, 81));
        QFont font1;
        font1.setPointSize(48);
        font1.setBold(true);
        font1.setItalic(true);
        label->setFont(font1);
        txt_id = new QLineEdit(frame);
        txt_id->setObjectName(QString::fromUtf8("txt_id"));
        txt_id->setGeometry(QRect(180, 210, 113, 21));
        txt_id->setStyleSheet(QString::fromUtf8("background: rgb(94, 94, 94)"));
        txt_nombre = new QLineEdit(frame);
        txt_nombre->setObjectName(QString::fromUtf8("txt_nombre"));
        txt_nombre->setGeometry(QRect(180, 250, 113, 21));
        txt_nombre->setStyleSheet(QString::fromUtf8("background: rgb(94, 94, 94)"));
        txt_anio = new QLineEdit(frame);
        txt_anio->setObjectName(QString::fromUtf8("txt_anio"));
        txt_anio->setGeometry(QRect(180, 300, 113, 21));
        txt_anio->setStyleSheet(QString::fromUtf8("background: rgb(94, 94, 94)"));
        txt_genero = new QLineEdit(frame);
        txt_genero->setObjectName(QString::fromUtf8("txt_genero"));
        txt_genero->setGeometry(QRect(180, 340, 113, 21));
        txt_genero->setStyleSheet(QString::fromUtf8("background: rgb(94, 94, 94)"));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(50, 140, 241, 41));
        QFont font2;
        font2.setPointSize(30);
        font2.setBold(true);
        font2.setItalic(true);
        label_2->setFont(font2);
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(130, 200, 31, 31));
        QFont font3;
        font3.setPointSize(20);
        font3.setBold(true);
        font3.setItalic(false);
        label_3->setFont(font3);
        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(70, 240, 91, 31));
        label_4->setFont(font3);
        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(100, 290, 61, 31));
        label_5->setFont(font3);
        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(80, 330, 81, 31));
        label_6->setFont(font3);
        btt_agregarPEli = new QPushButton(frame);
        btt_agregarPEli->setObjectName(QString::fromUtf8("btt_agregarPEli"));
        btt_agregarPEli->setGeometry(QRect(280, 420, 100, 32));
        btt_verReporte = new QPushButton(frame);
        btt_verReporte->setObjectName(QString::fromUtf8("btt_verReporte"));
        btt_verReporte->setGeometry(QRect(410, 420, 100, 32));
        btt_verReporte_2 = new QPushButton(frame);
        btt_verReporte_2->setObjectName(QString::fromUtf8("btt_verReporte_2"));
        btt_verReporte_2->setGeometry(QRect(340, 470, 100, 32));
        btt_ejemplo = new QPushButton(frame);
        btt_ejemplo->setObjectName(QString::fromUtf8("btt_ejemplo"));
        btt_ejemplo->setGeometry(QRect(530, 170, 141, 61));
        btt_ejemplo->setStyleSheet(QString::fromUtf8("background :rgb(255, 38, 0)"));
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
        label->setText(QCoreApplication::translate("MainWindow", "Ejemplo 2", nullptr));
        txt_id->setText(QString());
        txt_nombre->setText(QString());
        txt_anio->setText(QString());
        txt_genero->setText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "Agregar pelicula", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "ID:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Nombre:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Anio:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "genero:", nullptr));
        btt_agregarPEli->setText(QCoreApplication::translate("MainWindow", "Agregar", nullptr));
        btt_verReporte->setText(QCoreApplication::translate("MainWindow", "Ver Reporte", nullptr));
        btt_verReporte_2->setText(QCoreApplication::translate("MainWindow", "ventana3", nullptr));
        btt_ejemplo->setText(QCoreApplication::translate("MainWindow", "EJEmplo clase", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
