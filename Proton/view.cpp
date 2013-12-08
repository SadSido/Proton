#include "view.h"

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

// **************************************************************************************************

}
