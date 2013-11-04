#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>

namespace Proton
{

// **************************************************************************************************

class Scene : public QGraphicsScene
{
    Q_OBJECT

    typedef QGraphicsScene Base;

public:
    explicit Scene(QObject *parent = 0);
    virtual ~Scene();
};

// **************************************************************************************************

class View : public QGraphicsView
{
    Q_OBJECT

    typedef QGraphicsView Base;

public:
    explicit View(QWidget *parent = 0);
    virtual ~View();
};

// **************************************************************************************************

} // namespace

#endif
