#include "items.h"
#include <assert.h>

namespace
{

//**************************************************************************************************

template <typename ITEMTYPE>
Proton::BaseItem * createItemByType(Proton::Scene * scene, Proton::GameDesc::Ref game, const QString &type, const QString &name)
{ return new ITEMTYPE(scene); }

//**************************************************************************************************

}

namespace Proton
{

//**************************************************************************************************

BaseItem::BaseItem(Scene *scene)
: m_scene(scene)
{
}

BaseItem::~BaseItem()
{
}

// **************************************************************************************************

CardItem::CardItem(Scene * scene)
: BaseItem(scene)
{
}

CardItem::~CardItem()
{
}

//**************************************************************************************************

DeckItem::DeckItem(Scene * scene)
: BaseItem(scene)
{
    // let's have some test cards:
}

DeckItem::~DeckItem()
{
    // we own all undealt cards, so must delete:
    for (auto it = m_cards.begin(); it != m_cards.end(); ++it)
    { delete (*it); }
}

void DeckItem::dealCard()
{
    // the deck was depleted:
    if (m_cards.empty()) { return; }

    // pass the ownership to the scene:
    CardItem * topdeck = m_cards.back();
    m_scene->addItem(topdeck);

    // remove from the list of cards:
    m_cards.pop_back();
}

// **************************************************************************************************

BaseItem * createItem(Scene * scene, GameDesc::Ref game, const QString &type, const QString &name)
{
    if (type == tag_deck)
    { return createItemByType<DeckItem>(scene, game, type, name); }

    assert(false);
    return NULL;
}

// **************************************************************************************************
}

