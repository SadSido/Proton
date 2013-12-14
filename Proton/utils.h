#ifndef UTILS_H
#define UTILS_H

#include <QtCore>

namespace Proton
{

// **************************************************************************************************

// parsing mischellaneous stuff from strings:

QString parseSingle (QString::const_iterator &it);
QString parseToken  (QString::const_iterator &it);
QString parseQuotes (QString::const_iterator &it);
QString parseLine   (QString::const_iterator &it);

// **************************************************************************************************

}

#endif // UTILS_H
