#ifndef GAMESTATEWORLD_H
#define GAMESTATEWORLD_H

#include <GameState.h>
#include "GameWorld.h"
#include <SFML/Graphics.hpp>

enum class ActionState { NONE, PANNING };



class GameStateWorld : public GameState
{
    public:

    GameStateWorld(Game* game);
    ~GameStateWorld(){};

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();

    private:

    //special gui view for gamestate-world.
    sf::View m_guiView;
    //camera for viewing the world grid
    //TODO: support a list of gridviews to enable multiple viewports
    std::shared_ptr<sf::View> m_gridView;

    //Currently loaded gameworld.
    GameWorld m_gameWorld;

    //properties related to view controls.
    ActionState m_actionState;
    sf::Vector2i m_panningAnchor;
    float m_zoomLevel;

    //private helper functions
    bool handleMouseInputs(sf::Event event);
    bool handleKeyboardInputs(sf::Event event);
    bool handleOther(sf::Event event);

    void updateWasdMovement(const float dt);

    bool m_showFps = true;
};


#endif // GAMESTATEWORLD_H
