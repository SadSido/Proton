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
    // create scene. I wonder whether it is a cyclic reference:

    auto scene = new Scene(this);
    this->setScene(scene);

    // init custom background brush:

    QPixmap bgPixmap(":/proton/backgr/bg_dotted.png");
    setBackgroundBrush(bgPixmap);
}

View::~View()
{
}

// **************************************************************************************************

}
