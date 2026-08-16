#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../pelicula/pelicula.h"
#include <QStandardItemModel>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // agregar directores al ui del combo box
    matriz.definirEtiquetaFila(0, "Francis Ford Coppola");
    matriz.definirEtiquetaFila(1, "Quentin Tarantino");
    matriz.definirEtiquetaFila(2, "Christopher Nolan");
    matriz.definirEtiquetaFila(3, "Peter Jackson");

    ui->cbx_directores->addItem("Francis Ford Coppola", 0);
    ui->cbx_directores->addItem("Quentin Tarantino", 1);
    ui->cbx_directores->addItem("Christopher Nolan", 2);
    ui->cbx_directores->addItem("Peter Jackson", 3);



    // generos
    matriz.definirEtiquetaColumna(0, "Drama");
    matriz.definirEtiquetaColumna(1, "Thriller");
    matriz.definirEtiquetaColumna(2, "Ciencia Ficcion");
    matriz.definirEtiquetaColumna(3, "Fantasia");
    matriz.definirEtiquetaColumna(4, "Accion");
    matriz.definirEtiquetaColumna(5, "Comedia");

    ui->cbx_genero->addItem("Drama", 0);
    ui->cbx_genero->addItem("Thriller", 1);
    ui->cbx_genero->addItem("Ciencia Ficcion", 2);
    ui->cbx_genero->addItem("Fantasia", 3);
    ui->cbx_genero->addItem("Accion", 4);
    ui->cbx_genero->addItem("Comedia", 5);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btt_AgregarPeli_clicked()
{
    // obtener info del texto - para pelis
    QString titulo = ui->txt_titulo->text();
    QString anioTexto = ui->txt_anio->text();
    QString duracionTexto = ui->txt_duracion->text();


    // comvertir anio y duracion a integer
    bool anioValido;
    bool duracionValida;

    int anio = anioTexto.toInt(&anioValido);
    int duracion = duracionTexto.toInt(&duracionValida);

    // obtener info del combo box
    int fila = ui->cbx_directores->currentData().toInt();
    QString director = ui->cbx_directores->currentText();


    int columna = ui->cbx_genero->currentData().toInt();
    QString genero = ui->cbx_genero->currentText();


    // pelicula:
    Pelicula* pelicula = new Pelicula(
        titulo.toStdString(),
        director.toStdString(),
        duracion,
        anio,
        genero.toStdString()
        );

    matriz.insertar(
        fila,
        columna,
        pelicula
        );

    actualizarTablaMatriz();

    matriz.mostrar();
    matriz.exportarDOT("matriz_GUI");


    QMessageBox::information(
        this,
        "Película agregada",
        "La película se agregó correctamente a la matriz."
        );

    ui->txt_titulo->clear();
    ui->txt_anio->clear();
    ui->txt_duracion->clear();

    ui->txt_titulo->setFocus();




}


void MainWindow::actualizarTablaMatriz()
{
    QStandardItemModel* modelo = new QStandardItemModel(4, 6, this);

    // Encabezados de columnas
    modelo->setHorizontalHeaderLabels({
        "Drama",
        "Thriller",
        "Ciencia Ficcion",
        "Fantasia",
        "Accion",
        "Comedia"
    });

    // Encabezados de filas
    modelo->setVerticalHeaderLabels({
        "Francis Ford Coppola",
        "Quentin Tarantino",
        "Christopher Nolan",
        "Peter Jackson"
    });

    // Recorrer toda la matriz
    for (int fila = 0; fila < 4; fila++) {

        for (int columna = 0; columna < 6; columna++) {

            std::string contenido =
                matriz.obtenerContenidoCelda(fila, columna);

            if (!contenido.empty()) {

                QStandardItem* item =
                    new QStandardItem(
                        QString::fromStdString(contenido)
                        );

                modelo->setItem(fila, columna, item);
            }
        }
    }

    ui->table_matriz->setModel(modelo);

    ui->table_matriz->resizeColumnsToContents();
    ui->table_matriz->resizeRowsToContents();
}

void MainWindow::on_btt_AgregarDirector_clicked()
{

}


void MainWindow::on_btt_AgregarGenero_clicked()
{

}

