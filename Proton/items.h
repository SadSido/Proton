#ifndef ITEMS_H
#define ITEMS_H

#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QVector>
#include "view.h"
#include "game.h"

namespace Proton
{

//**************************************************************************************************

class BaseItem : public QObject, public QGraphicsPixmapItem
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
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal opacity  READ opacity  WRITE setOpacity)

public:
    explicit CardItem(Scene * scene, const QPixmap &face, const QPixmap &cover);
    virtual ~CardItem();

    // available actions:
    void fadeIn();
    void changeTapState();

private:
    // interface events:
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event) override;

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

    // available actions:
    void dealCard();

private:
    // interface events:
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event) override;

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
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)

public:
    explicit DiceItem(Scene * scene, GameDesc::Ref game, const QString &name);
    virtual ~DiceItem();

    // available actions:
    void reroll();

public slots:
    // animation callbacks:
    void setRandomFace();

private:
    // interface events:
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * event) override;

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
