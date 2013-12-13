#include "game.h"
#include "utils.h"
#include <assert.h>

namespace Proton
{

//**************************************************************************************************

QString ItemDesc::set(const QString &key, const QString &val)
{ m_data[key] = val; return val; }

QString ItemDesc::get(const QString &key)
{ return m_data[key]; }

//**************************************************************************************************

GameDesc::GameDesc()
{}

GameDesc::GameDesc(const QString &content)
{
    auto it = content.begin();
    while (!it->isNull())
    {
        QString token = Proton::parseToken(it);

        if (token == "//")
        { Proton::parseLine(it); }

        else if (token == "deck")
        { this->parseDeck(it); }

        else if (token == "token")
        { this->parseToken(it); }

        else if (token == "dice")
        { this->parseDice(it); }
    }
}

// parsing helpers:

void GameDesc::parseDeck(QString::const_iterator &it)
{
    QString name  = Proton::parseQuotes(it);
    QString brace = Proton::parseToken(it);

    if (name.isEmpty())
    { return; /* error : no name stated */ }

    if (m_decks.find(name) != m_decks.end())
    { return; /* error : deck name redefinition */ }

    ItemDesc::Ref item (new ItemDesc());
    m_decks[name] = item;

    while (!it->isNull())
    {
        QString key = Proton::parseToken(it);
        if (key == "}") { break; }

        QString col = Proton::parseToken(it);
        QString val = Proton::parseToken(it);

        if (!key.isEmpty() && col == ":" && !val.isEmpty())
        { item->set(key, val); }
    }
}

void GameDesc::parseToken(QString::const_iterator &it)
{
    QString name = parseQuotes(it);
}

void GameDesc::parseDice(QString::const_iterator &it)
{
    QString name = parseQuotes(it);
}

// **************************************************************************************************

} // namespace
