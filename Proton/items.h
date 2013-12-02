#ifndef ITEMS_H
#define ITEMS_H

#include <QGraphicsPixmapItem>

namespace Proton
{

//**************************************************************************************************

class BaseItem : public QGraphicsPixmapItem
{
public:
    explicit BaseItem();
    virtual ~BaseItem();
};

//**************************************************************************************************

class CardItem : public BaseItem
{
public:
    explicit CardItem();
    virtual ~CardItem();

private:
    QPixmap m_face;
    QPixmap m_cover;
};

// **************************************************************************************************

class DeckItem : public BaseItem
{
public:
    explicit DeckItem();
    virtual ~DeckItem();
};

// **************************************************************************************************

} // namespace

#endif
