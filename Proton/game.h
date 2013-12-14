#ifndef GAME_H
#define GAME_H

#include <QSharedPointer>
#include <QMap>
#include <QtCore>

namespace Proton
{

//**************************************************************************************************

struct ParseError
{
    explicit ParseError(const QString &newName, const QString &newDesc)
    : name(newName), desc(newDesc) {}

    QString name;
    QString desc;
};

//**************************************************************************************************

// general description of single game's item.

class ItemDesc
{
public:
    typedef QSharedPointer<ItemDesc> Ref;

    QString set(const QString &key, const QString &val);
    QString get(const QString &key);

private:
    QMap<QString, QString> m_data;
};

//**************************************************************************************************

// descriptor of the game stuff : decks, tokens, dices, play fields and all the stuff.
// You may query a lot of interesting information from this descriptor:

class GameDesc
{
public:
    typedef QSharedPointer<GameDesc> Ref;

    explicit GameDesc();
    explicit GameDesc(const QString &content);

    inline bool hasDeck(const QString &name) const
    { return m_decks.find(name) != m_decks.end(); }

private:
    QMap<QString, ItemDesc::Ref> m_decks;

private:
    void parseDeck  (QString::const_iterator &it);
    void parseDice  (QString::const_iterator &it);
    void parseToken (QString::const_iterator &it);
};

// **************************************************************************************************

} // namespace

#endif // GAME_H
