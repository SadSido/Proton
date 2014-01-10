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
    qDebug() << "View :: dragEnterEvent " << event->mimeData()->formats();

    auto mime = event->mimeData();
    (mime->hasText()) ? event->accept() : event->ignore();
}

void View::dragMoveEvent(QDragMoveEvent *event)
{
    event->accept();
}

void View::dropEvent(QDropEvent *event)
{
    qDebug() << "View :: dropEvent " << event->mimeData()->text();
    event->accept();
}
// **************************************************************************************************

}
