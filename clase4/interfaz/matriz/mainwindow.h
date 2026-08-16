#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../../matriz/MatrizDispersa.h"
#include <QMessageBox>


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
    void on_btt_AgregarPeli_clicked();

    void on_btt_AgregarDirector_clicked();

    void on_btt_AgregarGenero_clicked();

private:
    Ui::MainWindow *ui;
    MatrizDispersa matriz;
      void actualizarTablaMatriz();

};
#endif // MAINWINDOW_H
