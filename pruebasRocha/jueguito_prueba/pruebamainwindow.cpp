#include "pruebamainwindow.h"
#include "./ui_pruebamainwindow.h"

PruebaMainWindow::PruebaMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PruebaMainWindow)
{
    ui->setupUi(this);
}

PruebaMainWindow::~PruebaMainWindow()
{
    delete ui;
}
