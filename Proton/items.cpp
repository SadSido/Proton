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

QPropertyAnimation * animateProperty(QObject *target, const QByteArray &name, const QVariant &from, const QVariant &to)
{
    static const int s_duration = 150;
    auto anim = new QPropertyAnimation(target, name);

    anim->setDuration(s_duration);
    anim->setStartValue(from);
    anim->setEndValue(to);
    anim->setEasingCurve(QEasingCurve::InOutBounce);
    anim->start(QAbstractAnimation::DeleteWhenStopped);

    return anim;
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
    this->setTransformOriginPoint(this->boundingRect().center());
}

CardItem::~CardItem()
{
}

void CardItem::fadeIn()
{
    const qreal oldalpha = 0.0;
    const qreal newalpha = 1.0;

    animateProperty(this, "opacity", oldalpha, newalpha);
}

void CardItem::changeTapState()
{
    const qreal oldangle = rotation();
    const qreal newangle = 90.0 - oldangle;

    animateProperty(this, "rotation", oldangle, newangle);
}

void CardItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent*)
{ changeTapState(); }

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

// public slots:


void DeckItem::dealCard()
{
    // the deck was depleted:
    if (m_cards.empty()) { return; }

    // pass the ownership to the scene:
    CardItem * topdeck = m_cards.back();
    m_scene->addItem(topdeck);

    // remove from the list of cards:
    m_cards.pop_back();

    // position properly:
    auto pos = this->pos();
    auto off = this->boundingRect().size() / 10;

    topdeck->setPos(pos.x() + off.width(), pos.y() + off.height());
    topdeck->fadeIn();
}

void DeckItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent*)
{ dealCard(); }

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
        setRandomFace();
    }
}

DiceItem::~DiceItem()
{
}

// public actions:

void DiceItem::reroll()
{
    const qreal oldangle = 0.0f;
    const qreal newangle = 360.0f;

    auto anim = animateProperty(this, "rotation", oldangle, newangle);
    connect(anim, SIGNAL(finished()), this, SLOT(setRandomFace()));
}

// slots:

void DiceItem::setRandomFace()
{
    if (!m_faces.empty())
    {
        auto faceNo = qrand() % m_faces.size();
        this->setPixmap(m_faces[faceNo]);
        this->setTransformOriginPoint(this->boundingRect().center());
    }
}

// mouse events:

void DiceItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent*)
{ reroll(); }

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

