#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btt_agregarArtista_clicked()
{

    int id = ui->txt_id->text().toInt();
    QString nombre = ui->txt_nombre->text();
    QString genero = ui->txt_genero->text();

    Cantante cantante(
        id,
        nombre.toStdString(),
        genero.toStdString()
        );

    listaCantantes.insertar(cantante);
    listaCantantes.graficar("lista_circular_UI");


}

