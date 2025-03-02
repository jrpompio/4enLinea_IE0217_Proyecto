#ifndef PRUEBAMAINWINDOW_H
#define PRUEBAMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class PruebaMainWindow;
}
QT_END_NAMESPACE

class PruebaMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    PruebaMainWindow(QWidget *parent = nullptr);
    ~PruebaMainWindow();

private:
    Ui::PruebaMainWindow *ui;
};
#endif // PRUEBAMAINWINDOW_H
