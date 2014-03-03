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

    emit onItemDropped(type, name, mapToScene(event->pos()));

    qDebug() << "View :: dropEvent " << type << name;
    event->accept();
}

// wheel event:

void View::wheelEvent(QWheelEvent* event)
{

    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    // Scale the view / do the zoom
    double scaleFactor = 1.15;
    if(event->delta() > 0) {
        // Zoom in
        scale(scaleFactor, scaleFactor);
    } else {
        // Zooming out
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }

    auto brush = this->backgroundBrush();
    brush.setTransform(this->transform().inverted());
    this->setBackgroundBrush(brush);

    // Don't call superclass handler here
    // as wheel is normally used for moving scrollbars
}

// **************************************************************************************************

}
