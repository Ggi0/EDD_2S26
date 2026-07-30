#ifndef VENTANA3_H
#define VENTANA3_H

#include <QMainWindow>

namespace Ui {
class ventana3;
}

class ventana3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit ventana3(QWidget *parent = nullptr);
    ~ventana3();

private slots:
    void on_btt_regresar_clicked();

private:
    Ui::ventana3 *ui;
};

#endif // VENTANA3_H
