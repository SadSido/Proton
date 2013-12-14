#include "utils.h"

namespace
{

// **************************************************************************************************

const QString spaces = " \n\r\t";
const QString digits = "0123456789";
const QString quotes = "\"";
const QString newlns = "\r\n";

void skipWhile(QString::const_iterator &it, const QString &pattern)
{
    while (!it->isNull() && pattern.indexOf(*it) != (-1)) { ++ it; }
}

void skipUntil(QString::const_iterator &it, const QString &pattern)
{
    while (!it->isNull() && pattern.indexOf(*it) == (-1)) { ++ it; }
}

void skipAfter(QString::const_iterator &it, const QString &pattern)
{
    skipUntil(it, pattern);
    skipWhile(it, pattern);
}

// **************************************************************************************************

}

namespace Proton
{

// **************************************************************************************************

QString parseSingle(QString::const_iterator &it)
{
    skipWhile(it, spaces);
    return (*it == '"') ? parseQuotes(it) : parseToken(it);
}

QString parseToken(QString::const_iterator &it)
{
    skipWhile(it, spaces);
    auto beg = it;
    skipUntil(it, spaces);
    return QString(beg, it - beg);
}

QString parseQuotes(QString::const_iterator &it)
{
    skipUntil(it, quotes);
    auto beg = ++ it;
    skipUntil(it, quotes);
    auto end = it ++;
    return QString(beg, end - beg);
}

QString parseLine(QString::const_iterator &it)
{
    auto beg = it;
    skipUntil(it, newlns);
    auto end = it;
    skipWhile(it, newlns);
    return QString(beg, end - beg);
}

// **************************************************************************************************

}
