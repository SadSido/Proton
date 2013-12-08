#ifndef GAME_H
#define GAME_H

#include <QScopedPointer>
#include <QFile>

namespace Proton
{

//**************************************************************************************************

// descriptor of the game stuff : decks, tokens, dices, play fields and all the stuff.
// You may query a lot of interesting information from this descriptor:

class GameDesc
{
public:
    typedef QScopedPointer<GameDesc> Ref;

    explicit GameDesc();
    explicit GameDesc(QFile &file);
};

// **************************************************************************************************

} // namespace

#endif // GAME_H
