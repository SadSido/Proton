#ifndef GAME_H
#define GAME_H

#include <QSharedPointer>
#include <QMap>
#include <QtCore>

namespace Proton
{

//**************************************************************************************************

extern const char * const tag_deck;
extern const char * const tag_dice;
extern const char * const tag_token;

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
    QString get(const QString &key) const;
    bool    has(const QString &key) const;

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
    typedef QMap<QString, ItemDesc::Ref> ItemMap;

    explicit GameDesc();
    explicit GameDesc(const QString &content);

    // get the necessary maps:

    inline ItemMap & getItems(const QString &type)
    { return m_map[type]; }

    inline ItemMap & getDecks()
    { return getItems(tag_deck); }

    inline ItemMap & getDices()
    { return getItems(tag_dice); }

    inline ItemMap & getTokens()
    { return getItems(tag_token); }

    // additional info:

    QString getPath() const
    { return m_path; }

private:
    typedef QMap<QString, ItemMap> GameMap;

    GameMap m_map;
    QString m_path;

private:
    void ensureMaps ();
    void parseItem  (QString::const_iterator &it, ItemMap &into);
};

// **************************************************************************************************

} // namespace

#endif // GAME_H
