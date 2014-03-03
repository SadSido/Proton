#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QScopedPointer>

namespace Proton
{

// **************************************************************************************************

class Scene : public QGraphicsScene
{
    Q_OBJECT

public:
    typedef QScopedPointer<Scene> Ref;
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

    virtual void dragEnterEvent(QDragEnterEvent *event) override;
    virtual void dragMoveEvent(QDragMoveEvent *event) override;
    virtual void dropEvent(QDropEvent *event) override;
    virtual void wheelEvent(QWheelEvent* event) override;

signals:
    void onItemDropped(const QString &type, const QString &name, const QPointF &pos);
};

// **************************************************************************************************

} // namespace

#endif
