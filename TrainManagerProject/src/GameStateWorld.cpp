#include "GameState.h"
#include "GameStateWorld.h"
#include <SFML/Graphics.hpp>
#include <iostream>

const float VIEW_WASD_SPEED = 1000; // px/s2

GameStateWorld::GameStateWorld(Game* game):
    m_gameWorld(game)
{
    m_gridView = std::make_shared<sf::View>();
    m_game = game;
    sf::Vector2f pos = sf::Vector2f(m_game->m_window.getSize());
    m_guiView.setSize(pos);
    m_mainView.setSize(pos);
    m_gridView->setSize(pos);
    pos *= 0.5f;
    m_guiView.setCenter(pos);
    m_mainView.setCenter(pos);
    m_gridView->setCenter(pos);

    //set view to draw gameworld on
    m_gameWorld.setView(m_gridView);

    m_zoomLevel = 1.0f;
    m_actionState = ActionState::NONE;

    //always generate random world for now
    m_gameWorld.generateRandomMap();


}

void GameStateWorld::draw(const float dt)
{


    m_game->m_window.clear(sf::Color::Black);
    m_game->m_window.setView(m_guiView);
    m_game->m_window.draw(m_game->m_background);

    m_game->m_window.setView(*m_gridView);

    m_game->m_window.draw(m_gameWorld);

    m_game->m_window.setView(m_mainView);

    return;
}

void GameStateWorld::update(const float dt)
{

    updateWasdMovement(dt);
    return;
}

void GameStateWorld::handleInput()
{
    sf::Event event;

    while(m_game->m_window.pollEvent(event))
    {
        if(handleMouseInputs(event)) break;
        if(handleKeyboardInputs(event)) break;
        if(handleOther(event)) break;

    }
    return;
}


bool GameStateWorld::handleMouseInputs(sf::Event event)
{
    //Pass certain mouse events down to gameworld if not used here?
    bool eventMatch = false;
    switch(event.type)
    {
        case sf::Event::MouseMoved:
        {
            /* Pan the camera */
            if(m_actionState == ActionState::PANNING)
            {
                sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(m_game->m_window) - m_panningAnchor);
                m_gridView->move(-1.0f * pos * m_zoomLevel);
                m_panningAnchor = sf::Mouse::getPosition(m_game->m_window);
            }
            eventMatch = true;
            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            /* Start panning */
            if(event.mouseButton.button == sf::Mouse::Right)
            {
                if(m_actionState != ActionState::PANNING)
                {
                    m_actionState = ActionState::PANNING;
                    m_panningAnchor = sf::Mouse::getPosition(m_game->m_window);
                }
            }
            eventMatch = true;
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            /* Stop panning */
            if(event.mouseButton.button == sf::Mouse::Right)
            {
                m_actionState = ActionState::NONE;
            }
            eventMatch = true;
            break;
        }

        /* Zoom the view */
        case sf::Event::MouseWheelMoved:
        {

            sf::Vector2f windowSize = sf::Vector2f(m_game->m_window.getSize());
            m_gridView->setSize(windowSize.x, windowSize.y);
            if(event.mouseWheel.delta < 0)
            {
                m_zoomLevel *= 1.5f;

            }
            else
            {
                m_zoomLevel *= 0.5f;

            }
            if ( m_zoomLevel > 3) m_zoomLevel = 3;
            if ( m_zoomLevel < 0.25) m_zoomLevel = 0.25;

            m_gridView->zoom(m_zoomLevel);
            eventMatch = true;
            break;
        }
        default: break;
    }

    if (!eventMatch)
    {
        //Process input in gameworld.
        //should look at sfml ui before doing too much with this.
    }

    return eventMatch;
}

bool GameStateWorld::handleKeyboardInputs(sf::Event event)
{
    bool eventMatch = false;
    switch(event.type)
    {

        case sf::Event::KeyPressed:
        {
            if(event.key.code == sf::Keyboard::Escape)
            {
                m_game->popState();
            }
            else if(event.key.code == sf::Keyboard::G)
            {
                m_gameWorld.generateRandomMap();
            }
            eventMatch = true;
            break;

        }
        default: break;

    }
    return eventMatch;
}

bool GameStateWorld::handleOther(sf::Event event)
{
    bool eventMatch = false;
    switch(event.type)
    {
        /* Close the window */
        case sf::Event::Closed:
        {
            m_game->m_window.close();
            eventMatch = true;
            break;
        }
        /* Resize the window */
        case sf::Event::Resized:
        {
            m_mainView.setSize(event.size.width, event.size.height);
            m_gridView->setSize(event.size.width, event.size.height);
            m_guiView.setSize(event.size.width, event.size.height);
            m_game->m_background.setPosition(m_game->m_window.mapPixelToCoords(sf::Vector2i(0, 0), m_guiView));
            m_game->m_background.setScale(
                float(event.size.width) / float(m_game->m_background.getTexture()->getSize().x),
                float(event.size.height) / float(m_game->m_background.getTexture()->getSize().y));

            m_mainView.setCenter(event.size.width / 2, event.size.height / 2);
            m_gridView->zoom(m_zoomLevel);
            eventMatch = true;
            break;
        }
        default: break;
    }

    return eventMatch;
}

void GameStateWorld::updateWasdMovement(const float dt)
{

    sf::Vector2f viewVelocity;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        viewVelocity.x = -VIEW_WASD_SPEED * dt * m_zoomLevel; // pan faster if zoomed out (larger zoom level)
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        viewVelocity.x = VIEW_WASD_SPEED * dt * m_zoomLevel;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        viewVelocity.y = -VIEW_WASD_SPEED * dt * m_zoomLevel;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        viewVelocity.y = VIEW_WASD_SPEED * dt * m_zoomLevel;
    }
    m_gridView->move(viewVelocity);
}
