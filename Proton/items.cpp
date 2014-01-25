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
    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

BaseItem::~BaseItem()
{
}

// **************************************************************************************************

CardItem::CardItem(Scene * scene, const QPixmap &face, const QPixmap &cover)
: BaseItem(scene), m_face(face), m_cover(cover)
{
    this->setPixmap(face);
}

CardItem::~CardItem()
{
}

//**************************************************************************************************

DeckItem::DeckItem(Scene * scene, GameDesc::Ref game, const QString &name)
: BaseItem(scene)
{
    qDebug() << "DeckItem :: constructor" << name;

    // get the descriptor:

    auto items = game->getDecks();
    auto item  = items.find(name);

    if (item != items.end())
    {
        const QString path = game->getPath();
        const QString subd = (*item)->get("dir");
        const QString covr = (*item)->get("cover");

        // base path for stuff:

        QDir dir(path); dir.cd(subd);
        auto files = dir.entryList(QStringList(), QDir::Files, QDir::Name);

        // fetch the cover:

        QPixmap cover(dir.absoluteFilePath(covr));
        this->setPixmap(cover);

        // fetch the cards:

        foreach (QString file , files)
        {
            // skip cover file:
            if (file == covr) { continue; }

            QPixmap face(dir.absoluteFilePath(file));

            auto cardItem = new CardItem(scene, face, cover);
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

TokenItem::TokenItem(Scene * scene, GameDesc::Ref game, const QString &name)
: BaseItem(scene)
{
    qDebug() << "TokenItem :: constructor" << name;

    // get the descriptor:

    auto items = game->getTokens();
    auto item  = items.find(name);

    if (item != items.end())
    {
        const QString path = game->getPath();
        const QString file = (*item)->get("file");

        // fetch the cover:

        QDir dir(path);
        QPixmap face(dir.absoluteFilePath(file));
        this->setPixmap(face);
    }
}

TokenItem::~TokenItem()
{
}

//**************************************************************************************************

DiceItem::DiceItem(Scene * scene, GameDesc::Ref game, const QString &name)
: BaseItem(scene), m_faceNo(0)
{
    qDebug() << "DiceItem :: constructor" << name;

    // get the descriptor:

    auto items = game->getDices();
    auto item  = items.find(name);

    if (item != items.end())
    {
        const QString path = game->getPath();
        const QString subd = (*item)->get("dir");

        // base path for stuff:

        QDir dir(path); dir.cd(subd);
        auto files = dir.entryList(QStringList(), QDir::Files, QDir::Name);

        // fetch the cards:

        foreach (QString file , files)
        {
            m_faces.push_back(QPixmap(dir.absoluteFilePath(file)));
        }

        // set initial face:
        if (!m_faces.empty())
        { this->setPixmap(m_faces[0]); }
    }
}

DiceItem::~DiceItem()
{
}

//**************************************************************************************************

BaseItem * createItem(Scene * scene, GameDesc::Ref game, const QString &type, const QString &name)
{
    if (type == tag_deck)
    { return createItemByType<DeckItem>(scene, game, name); }

    if (type == tag_token)
    { return createItemByType<TokenItem>(scene, game, name); }

    if (type == tag_dice)
    { return createItemByType<DiceItem>(scene, game, name); }

    assert(false);
    return NULL;
}

// **************************************************************************************************
}

