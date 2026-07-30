#ifndef VENTANA2_H
#define VENTANA2_H

#include <QWidget>
#include <QPixmap>

namespace Ui {
class ventana2;
}

class ventana2 : public QWidget
{
    Q_OBJECT

public:
    explicit ventana2(QWidget *parent = nullptr);
    ~ventana2();

private:
    Ui::ventana2 *ui;
};

#endif // VENTANA2_H
