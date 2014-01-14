#include "view.h"
#include <QMimeData>
#include <QtDebug>

namespace Proton
{

//**************************************************************************************************

Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
}

Scene::~Scene()
{
}

//**************************************************************************************************

View::View(QWidget *parent) : QGraphicsView(parent)
{
    // init custom background brush:

    QPixmap bgPixmap(":/proton/backgr/bg_dotted.png");
    setBackgroundBrush(bgPixmap);
}

View::~View()
{
}

// drag and drop events:

void View::dragEnterEvent(QDragEnterEvent *event)
{
    auto formats = event->mimeData()->formats();
    qDebug() << "View :: dragEnterEvent " << formats;

    bool formatOK = qFind(formats, "type-name-pair") != formats.end();
    (formatOK) ? event->accept() : event->ignore();
}

void View::dragMoveEvent(QDragMoveEvent *event)
{
    event->accept();
}

void View::dropEvent(QDropEvent *event)
{
    QDataStream stream(event->mimeData()->data("type-name-pair"));

    QString type; stream >> type;
    QString name; stream >> name;

    emit onItemDropped(type, name);

    qDebug() << "View :: dropEvent " << type << name;
    event->accept();
}
// **************************************************************************************************

}
