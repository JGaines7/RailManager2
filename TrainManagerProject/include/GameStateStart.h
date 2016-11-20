#ifndef GAMESTATESTART_H
#define GAMESTATESTART_H

#include <GameState.h>
#include <SFML/Graphics.hpp>
#include "UI_MainMenu.h"


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
    UI_MainMenu m_mainMenu;

    //utility
    void resizeWindow(float width, float height);


};

#endif // GAMESTATESTART_H
