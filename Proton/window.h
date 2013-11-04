#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>

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

private:
    Ui::Window *ui;
};

// **************************************************************************************************

} // namespace

#endif
