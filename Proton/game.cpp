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
const char * const err_param_redef = "parameter redefinition";
const char * const err_no_colon    = "missing colon after parameter";

//**************************************************************************************************

}

namespace Proton
{

//**************************************************************************************************

const char * const tag_deck  = "deck";
const char * const tag_dice  = "dice";
const char * const tag_token = "token";

//**************************************************************************************************

QString ItemDesc::set(const QString &key, const QString &val)
{
    m_data[key] = val;
    return val;
}

QString ItemDesc::get(const QString &key) const
{
    auto it = m_data.find(key);
    return (it != m_data.end()) ? (*it) : QString();
}

bool ItemDesc::has(const QString &key) const
{
    auto it = m_data.find(key);
    return it != m_data.end();
}

//**************************************************************************************************

GameDesc::GameDesc()
{
    // init empty maps:
    ensureMaps();
}

GameDesc::GameDesc(const QString &content)
{
    // init empty maps:
    ensureMaps();

    // parse incoming str:
    auto it = content.begin();
    while (!it->isNull())
    {
        QString token = Proton::parseToken(it);
        qDebug() << "GameDesc :: parse token" << token;

        if (token == "//")
        { Proton::parseLine(it); }

        else if (m_map.contains(token))
        { parseItem(it, m_map[token]); }

        else if (!token.isEmpty())
        { throw_if(token, err_bad_token, true); }
    }
}

// parsing helpers:

void GameDesc::ensureMaps()
{
    // the following sections are available:
    static const QString mapNames [] = {tag_deck, tag_dice, tag_token};
    static const size_t  mapCount = sizeof(mapNames) / sizeof(mapNames[0]);

    for (size_t no = 0; no < mapCount; ++ no)
    { m_map[mapNames[no]] = ItemMap(); }
}

void GameDesc::parseItem(QString::const_iterator &it, ItemMap &into)
{
    QString name  = Proton::parseSingle(it);
    QString brace = Proton::parseToken(it);

    qDebug() << "GameDesc :: item" << name;

    throw_if(name, err_no_brace,   brace != "{");
    throw_if(name, err_empty_name, name.isEmpty());
    throw_if(name, err_dupe_name,  into.contains(name));

    ItemDesc::Ref item (new ItemDesc());
    into[name] = item;

    while (!it->isNull())
    {
        QString key = Proton::parseToken(it);
        if (key == "}") { break; }

        QString col = Proton::parseToken(it);
        QString val = Proton::parseSingle(it);

        qDebug() << "GameDesc :: entry" << key << val;

        throw_if(key, err_empty_param, key.isEmpty());
        throw_if(key, err_empty_value, val.isEmpty());
        throw_if(key, err_param_redef, item->has(key));
        throw_if(key, err_no_colon,    col != ":");

        item->set(key, val);
    }
}

// **************************************************************************************************

} // namespace
