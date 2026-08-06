#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../../lista_circular/lista_circular.h"
#include "../../cantante/cantante.h"

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
    void on_btt_agregarArtista_clicked();

private:
    Ui::MainWindow *ui;
    ListaCircular listaCantantes;

};
#endif // MAINWINDOW_H
