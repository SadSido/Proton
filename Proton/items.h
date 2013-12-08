#ifndef ITEMS_H
#define ITEMS_H

#include <QGraphicsPixmapItem>
#include <QVector>
#include "view.h"

namespace Proton
{

//**************************************************************************************************

class BaseItem : public QGraphicsPixmapItem
{
public:
    explicit BaseItem(Scene * scene);
    virtual ~BaseItem();

protected:
    Scene * m_scene;
};

//**************************************************************************************************

class CardItem : public BaseItem
{
public:
    explicit CardItem(Scene * scene);
    virtual ~CardItem();

private:
    QPixmap m_face;
    QPixmap m_cover;
};

// **************************************************************************************************

class DeckItem : public BaseItem
{
public:
    explicit DeckItem(Scene * scene);
    virtual ~DeckItem();

public:
    void dealCard();

private:
    QVector<CardItem*> m_cards;
};

// **************************************************************************************************

} // namespace

#endif
