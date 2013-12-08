#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include "view.h"

// **************************************************************************************************

namespace Ui { class Window; }

// **************************************************************************************************

namespace Proton
{

// **************************************************************************************************

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    virtual ~Window();

public slots:
    void menu_OpenPrototype();

private:
    Ui::Window *ui;
    Scene * m_scene;

private:
    void connectMenuSignals();
};

// **************************************************************************************************

} // namespace

#endif
