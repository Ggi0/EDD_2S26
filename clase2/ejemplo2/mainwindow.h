#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../doubly_linked_list/doubly_linked_list.h"
#include "../pelicula/pelicula.h"
#include "ventana2.h"
#include "ventana3.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btt_agregarPEli_clicked();

    void on_btt_verReporte_clicked();

    void on_btt_verReporte_2_clicked();

private:
    Ui::MainWindow *ui;
    ListaDoble listaPeliculas;
};
#endif // MAINWINDOW_H
