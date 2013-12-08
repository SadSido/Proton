#include "window.h"
#include "ui_window.h"
#include <QFileDialog>

namespace Proton
{

// **************************************************************************************************

// c-tor and d-tor:

Window::Window(QWidget *parent) : QMainWindow(parent), ui(new Ui::Window)
{
    // layout all the stuff:
    ui->setupUi(this);

    // additional initialization:
    connectMenuSignals();

    // finally, create scene:
    m_scene = new Scene(this);
    ui->view->setScene(m_scene);
}

Window::~Window()
{
    delete ui;
}

// menu bar handlers:

void Window::menu_OpenPrototype()
{
    QString filename = QFileDialog::getOpenFileName(this);
}

// helpers:

void Window::connectMenuSignals()
{
    connect(ui->actionOpen_prototype, SIGNAL(triggered()), this, SLOT(menu_OpenPrototype()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
}

// **************************************************************************************************

} // namespace
