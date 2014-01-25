#ifndef ITEMS_H
#define ITEMS_H

#include <QGraphicsPixmapItem>
#include <QVector>
#include "view.h"
#include "game.h"

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
    explicit CardItem(Scene * scene, const QPixmap &face, const QPixmap &cover);
    virtual ~CardItem();

private:
    QPixmap m_face;
    QPixmap m_cover;
};

// **************************************************************************************************

class DeckItem : public BaseItem
{
public:
    explicit DeckItem(Scene * scene, GameDesc::Ref game, const QString &name);
    virtual ~DeckItem();

public:
    void dealCard();

private:
    QVector<CardItem*> m_cards;
};

// **************************************************************************************************

class TokenItem : public BaseItem
{
public:
    explicit TokenItem(Scene * scene, GameDesc::Ref game, const QString &name);
    virtual ~TokenItem();

private:
    QPixmap m_face;
};

// **************************************************************************************************

class DiceItem : public BaseItem
{
public:
    explicit DiceItem(Scene * scene, GameDesc::Ref game, const QString &name);
    virtual ~DiceItem();

private:
    int m_faceNo;
    QVector<QPixmap> m_faces;
};

// **************************************************************************************************

// factory function to create Graphic item from the prototype description:

BaseItem * createItem(Scene * scene, GameDesc::Ref game, const QString &type, const QString &name);

// **************************************************************************************************

} // namespace

#endif
