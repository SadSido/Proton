#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include "view.h"
#include "game.h"

// **************************************************************************************************

namespace Ui { class Window; }

// **************************************************************************************************

namespace Proton
{

class ListEntry : public QWidget
{
    Q_OBJECT

public:
    explicit ListEntry(QWidget *parent, const QString &type, const QString &name);
    virtual ~ListEntry();

    virtual void paintEvent(QPaintEvent * event) override;

private:
    QString m_name;
    QString m_type;
};

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
    Scene::Ref m_scene;
    GameDesc::Ref m_game;

private:
    void connectMenuSignals();
    void refillListViews();

    void loadPrototype(const QString &path);
};

// **************************************************************************************************

} // namespace

#endif
