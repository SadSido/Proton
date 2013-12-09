#include "game.h"
#include "utils.h"

namespace Proton
{

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
    QString name = parseQuotes(it);
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
