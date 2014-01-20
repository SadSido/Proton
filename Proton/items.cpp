#include "items.h"
#include <assert.h>

namespace
{

//**************************************************************************************************

template <typename ITEMTYPE>
Proton::BaseItem * createItemByType(Proton::Scene * scene, Proton::GameDesc::Ref game, const QString &name)
{
    try
    {
        auto item = new ITEMTYPE(scene, game, name);
        return item;
    }
    catch (...)
    { return NULL; }
}

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

DeckItem::DeckItem(Scene * scene, GameDesc::Ref game, const QString &name)
: BaseItem(scene)
{
    auto items = game->getDecks();
    auto item  = items.find(name);

    if (item != items.end())
    {
        const QString path = game->getPath();
        const QString subd = (*item)->get("dir");
        const QString covr = (*item)->get("cover");

        QDir dir(path); dir.cd(subd);
        auto files = dir.entryList(QStringList(), QDir::Files, QDir::Name);

        foreach (QString file , files)
        {
            QPixmap pixFace(dir.absoluteFilePath(file));
            QPixmap pixCovr(dir.absoluteFilePath(covr));

            auto cardItem = new CardItem(scene);
            m_cards.push_back(cardItem);
        }

    }
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
    { return createItemByType<DeckItem>(scene, game, name); }

    assert(false);
    return NULL;
}

// **************************************************************************************************
}

