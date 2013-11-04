#ifndef ITEMS_H
#define ITEMS_H

#include <QGraphicsPixmapItem>

namespace Proton
{

//**************************************************************************************************

class CardItem : public QGraphicsPixmapItem
{
    typedef QGraphicsPixmapItem Base;

public:
    explicit CardItem();
    virtual ~CardItem();
};

// **************************************************************************************************

} // namespace

#endif
