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


void MainWindow::on_btt_agregarPEli_clicked()
{
    // aqui va estar la logica de lo que debe de hacer el boton al presionarlo

    // Obtener datos de los QLineEdit
    int id = ui->txt_id->text().toInt();
    QString nombre = ui->txt_nombre->text();
    int anio = ui->txt_anio->text().toInt();
    QString genero = ui->txt_genero->text();


    listaPeliculas.insertarAlFinal(
        Pelicula(
            id,
            nombre.toStdString(),
            anio,
            genero.toStdString()
            )
        );

    listaPeliculas.graficar("lista_ui");


    // Limpiar las cajas de texto
    ui->txt_id->clear();
    ui->txt_nombre->clear();
    ui->txt_anio->clear();
    ui->txt_genero->clear();



}


void MainWindow::on_btt_verReporte_clicked()
{

    // Crear instancia de ventana2
    ventana2 *ventana = new ventana2(this);

    // Mostrar la ventana
    ventana->show();

}


void MainWindow::on_btt_verReporte_2_clicked()
{
    // creamos la ventana 3
    ventana3 *ventana = new ventana3(this);

    ventana->show();

    this->hide();

}

