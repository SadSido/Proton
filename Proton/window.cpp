#include "window.h"
#include "ui_window.h"
#include <QFileDialog>
#include <QMessageBox>

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

    // create default prototype:
    m_game.reset(new GameDesc());

    // finally, create scene:
    m_scene.reset(new Scene());
    ui->view->setScene(m_scene.data());
}

Window::~Window()
{
    delete ui;
}

// menu bar handlers:

void Window::menu_OpenPrototype()
{
    QString filename = QFileDialog::getOpenFileName(this);

    QFile file(filename);
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QString content(file.readAll());

        try
        {
            auto game = new GameDesc(content);
            m_game.reset(game);
        }
        catch (ParseError &pe)
        {
            const QString caption = "Failed to read file";
            const QString message = QString("%1 : %2").arg(pe.name, pe.desc);

            QMessageBox::warning(this, caption, message);
        }
    }
}

// helpers:

void Window::connectMenuSignals()
{
    connect(ui->actionOpen_prototype, SIGNAL(triggered()), this, SLOT(menu_OpenPrototype()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
}

// **************************************************************************************************

} // namespace
