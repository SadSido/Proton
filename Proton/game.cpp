#include "game.h"
#include "utils.h"
#include <assert.h>
#include <QDebug>

namespace
{
//**************************************************************************************************

void throw_if(const QString &name, const QString &desc, bool condition)
{ if (condition) { throw Proton::ParseError(name, desc); } }

//**************************************************************************************************

const char * const err_bad_token   = "unrecognized token";
const char * const err_no_brace    = "missing opening brace";
const char * const err_empty_name  = "name is empty";
const char * const err_dupe_name   = "name is used already";
const char * const err_empty_param = "parameter name is empty";
const char * const err_empty_value = "parameter value is empty";
const char * const err_no_colon    = "missing colon after parameter";

//**************************************************************************************************
}

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
        qDebug() << "GameDesc :: parse token" << token;

        if (token == "//")
        { Proton::parseLine(it); }

        else if (token == "deck")
        { this->parseDeck(it); }

        else if (token == "token")
        { this->parseToken(it); }

        else if (token == "dice")
        { this->parseDice(it); }

        else
        { throw_if(token, err_bad_token, !token.isEmpty()); }
    }
}

// parsing helpers:

void GameDesc::parseDeck(QString::const_iterator &it)
{
    QString name  = Proton::parseSingle(it);
    QString brace = Proton::parseToken(it);

    qDebug() << "GameDesc :: deck" << name;

    throw_if(name, err_no_brace,   brace != "{");
    throw_if(name, err_empty_name, name.isEmpty());
    throw_if(name, err_dupe_name,  hasDeck(name));

    ItemDesc::Ref item (new ItemDesc());
    m_decks[name] = item;

    while (!it->isNull())
    {
        QString key = Proton::parseToken(it);
        if (key == "}") { break; }

        QString col = Proton::parseToken(it);
        QString val = Proton::parseSingle(it);

        qDebug() << "GameDesc :: entry" << key << val;

        throw_if(key, err_empty_param, key.isEmpty());
        throw_if(key, err_empty_value, val.isEmpty());
        throw_if(key, err_no_colon,    col != ":");

        item->set(key, val);
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
