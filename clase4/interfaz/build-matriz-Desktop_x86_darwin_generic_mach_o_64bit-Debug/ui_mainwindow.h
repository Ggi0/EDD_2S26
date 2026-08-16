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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *frame;
    QLabel *label;
    QComboBox *cbx_directores;
    QPushButton *btt_AgregarDirector;
    QLineEdit *txt_director;
    QComboBox *cbx_genero;
    QPushButton *btt_AgregarGenero;
    QLineEdit *txt_genero;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *txt_titulo;
    QLineEdit *txt_duracion;
    QLineEdit *txt_anio;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QTableView *table_matriz;
    QPushButton *btt_AgregarPeli;
    QTableWidget *tableWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1111, 750);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 1091, 681));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 421, 61));
        QFont font;
        font.setPointSize(40);
        label->setFont(font);
        cbx_directores = new QComboBox(frame);
        cbx_directores->addItem(QString());
        cbx_directores->addItem(QString());
        cbx_directores->addItem(QString());
        cbx_directores->setObjectName(QString::fromUtf8("cbx_directores"));
        cbx_directores->setGeometry(QRect(820, 210, 131, 41));
        btt_AgregarDirector = new QPushButton(frame);
        btt_AgregarDirector->setObjectName(QString::fromUtf8("btt_AgregarDirector"));
        btt_AgregarDirector->setGeometry(QRect(180, 150, 100, 32));
        txt_director = new QLineEdit(frame);
        txt_director->setObjectName(QString::fromUtf8("txt_director"));
        txt_director->setGeometry(QRect(30, 160, 131, 21));
        cbx_genero = new QComboBox(frame);
        cbx_genero->addItem(QString());
        cbx_genero->addItem(QString());
        cbx_genero->addItem(QString());
        cbx_genero->setObjectName(QString::fromUtf8("cbx_genero"));
        cbx_genero->setGeometry(QRect(820, 250, 131, 41));
        btt_AgregarGenero = new QPushButton(frame);
        btt_AgregarGenero->setObjectName(QString::fromUtf8("btt_AgregarGenero"));
        btt_AgregarGenero->setGeometry(QRect(470, 150, 100, 32));
        txt_genero = new QLineEdit(frame);
        txt_genero->setObjectName(QString::fromUtf8("txt_genero"));
        txt_genero->setGeometry(QRect(320, 160, 131, 21));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(50, 100, 201, 41));
        QFont font1;
        font1.setPointSize(20);
        label_2->setFont(font1);
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(330, 100, 241, 41));
        label_3->setFont(font1);
        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(730, 30, 241, 41));
        label_4->setFont(font1);
        txt_titulo = new QLineEdit(frame);
        txt_titulo->setObjectName(QString::fromUtf8("txt_titulo"));
        txt_titulo->setGeometry(QRect(820, 110, 131, 21));
        txt_duracion = new QLineEdit(frame);
        txt_duracion->setObjectName(QString::fromUtf8("txt_duracion"));
        txt_duracion->setGeometry(QRect(820, 150, 131, 21));
        txt_anio = new QLineEdit(frame);
        txt_anio->setObjectName(QString::fromUtf8("txt_anio"));
        txt_anio->setGeometry(QRect(820, 180, 131, 21));
        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(750, 90, 51, 41));
        QFont font2;
        font2.setPointSize(18);
        label_5->setFont(font2);
        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(720, 140, 81, 41));
        label_6->setFont(font2);
        label_7 = new QLabel(frame);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(750, 180, 51, 41));
        label_7->setFont(font2);
        label_8 = new QLabel(frame);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(720, 210, 71, 41));
        label_8->setFont(font2);
        label_9 = new QLabel(frame);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(730, 250, 71, 41));
        label_9->setFont(font2);
        table_matriz = new QTableView(frame);
        table_matriz->setObjectName(QString::fromUtf8("table_matriz"));
        table_matriz->setGeometry(QRect(30, 250, 601, 401));
        btt_AgregarPeli = new QPushButton(frame);
        btt_AgregarPeli->setObjectName(QString::fromUtf8("btt_AgregarPeli"));
        btt_AgregarPeli->setGeometry(QRect(819, 300, 141, 41));
        tableWidget = new QTableWidget(frame);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        if (tableWidget->rowCount() < 5)
            tableWidget->setRowCount(5);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem9);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(670, 370, 361, 271));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1111, 22));
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
        label->setText(QCoreApplication::translate("MainWindow", "Ejemplo matriz dispersa", nullptr));
        cbx_directores->setItemText(0, QCoreApplication::translate("MainWindow", "opt1", nullptr));
        cbx_directores->setItemText(1, QCoreApplication::translate("MainWindow", "opt2", nullptr));
        cbx_directores->setItemText(2, QCoreApplication::translate("MainWindow", "opt3", nullptr));

        btt_AgregarDirector->setText(QCoreApplication::translate("MainWindow", "agregar", nullptr));
        cbx_genero->setItemText(0, QCoreApplication::translate("MainWindow", "opt1", nullptr));
        cbx_genero->setItemText(1, QCoreApplication::translate("MainWindow", "opt3", nullptr));
        cbx_genero->setItemText(2, QCoreApplication::translate("MainWindow", "opt2", nullptr));

        btt_AgregarGenero->setText(QCoreApplication::translate("MainWindow", "agregar", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Agregar director (fila)", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Agregar genero (columna)", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Agregar Pelicula", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "titulo:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "duracion:", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "anio:", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "director:", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "genero:", nullptr));
        btt_AgregarPeli->setText(QCoreApplication::translate("MainWindow", "agregar pelicula", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "New Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "New Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "New Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "New Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "New Column", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "New Row", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
