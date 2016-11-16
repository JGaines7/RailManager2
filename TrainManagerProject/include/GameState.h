#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Game.h"

class GameState
{
    public:

    Game* m_game;

    //main view of each gamestate. Should equal window size;
    //draw things like fps and debug info.  Rest should be in views specific to mode
    sf::View m_mainView;

    virtual void draw(const float dt) = 0;
    virtual void update(const float dt) = 0;
    virtual void handleInput() = 0;
    virtual ~GameState(){};

};

#endif // GAMESTATE_H
