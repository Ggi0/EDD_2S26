#include "ventana2.h"
#include "ui_ventana2.h"

ventana2::ventana2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ventana2)
{
    ui->setupUi(this);

    setWindowTitle("Reporte");

    // Hace que sea una ventana independiente
    setWindowFlags(Qt::Window);

    // Cargar imagen en el QLabel lbl_image
    QPixmap pixmap("../../../../doubly_linked_list/reporte/lista_ui.png");   // ruta al  archivo
    ui->lbl_image->setPixmap(
        pixmap.scaled(
            ui->lbl_image->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            )
        );
}

ventana2::~ventana2()
{
    delete ui;
}
