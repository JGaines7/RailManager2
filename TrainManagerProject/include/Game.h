#ifndef GAME_H
#define GAME_H

#include <stack>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class GameState;

class Game
{
    public:

    Game();
    ~Game();


    //getters
     TextureManager& getTextureManager() {return m_textureManager;}

    //member variables
    std::stack<GameState*> m_states;
    sf::RenderWindow m_window;
    TextureManager m_textureManager;

    //TODO why is this in overall game? Should we add shared sprites to overall game?

    sf::Sprite m_background;

    //font while we dont have resource manager
	sf::Font m_font;


    //functions
    void pushState(GameState* state);
    void popState();
    void changeState(GameState* state);
    GameState* peekState();

    //game utilities
    void drawFps(float dt);

    void gameLoop();

    private:

    void loadTextures();

};

#endif // GAME_H
