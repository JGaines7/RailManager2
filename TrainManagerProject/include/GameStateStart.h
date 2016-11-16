#ifndef GAMESTATESTART_H
#define GAMESTATESTART_H

//#include "testUI.h"
#include <GameState.h>
#include <SFML/Graphics.hpp>


class GameStateStart : public GameState
{
    public:

    GameStateStart(Game* game);
    ~GameStateStart(){};

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();

    private:

    void loadgame();


};

#endif // GAMESTATESTART_H
