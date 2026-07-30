#include "ventana3.h"
#include "ui_ventana3.h"

ventana3::ventana3(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ventana3)
{
    ui->setupUi(this);
}

ventana3::~ventana3()
{
    delete ui;
}

void ventana3::on_btt_regresar_clicked()
{
    // Recuperar el parent (MainWindow) y mostrarlo
    QWidget *p = this->parentWidget();
    if (p) {
        p->show();   // vuelve a mostrar la MainWindow
    }

    // Ocultar o cerrar ventana3
    this->close();
}

