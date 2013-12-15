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
    bool    has(const QString &key);

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

private:
    typedef QMap<QString, ItemDesc::Ref> ItemMap;
    typedef QMap<QString, ItemMap> GameMap;

    GameMap m_map;

private:
    void ensureMap (const QString &name);
    void parseItem (QString::const_iterator &it, ItemMap &into);
};

// **************************************************************************************************

} // namespace

#endif // GAME_H
