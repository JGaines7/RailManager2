#include "GameStateStart.h"

#include "GameStateWorld.h"
#include "GameState.h"
#include <iostream>
#include "imgui.h"


GameStateStart::GameStateStart(Game* game)
{
    m_game = game;
    sf::Vector2f pos = sf::Vector2f(m_game->m_window.getSize());
    m_mainView.setSize(pos);
    pos *= 0.5f;
    m_mainView.setCenter(pos);
}

void GameStateStart::loadgame()
{
    m_game->pushState(new GameStateWorld(m_game));

    return;
}

void GameStateStart::draw(const float dt)
{
    m_game->m_window.setView(m_mainView);

    m_game->m_window.clear(sf::Color::Black);

    m_game->m_background.setPosition(m_game->m_window.mapPixelToCoords(sf::Vector2i(0, 0)));
    m_game->m_background.setScale(
        m_mainView.getSize().x / float(m_game->m_background.getTexture()->getSize().x),
        m_mainView.getSize().y / float(m_game->m_background.getTexture()->getSize().y));

    m_game->m_window.draw(m_game->m_background);

    return;
}

void GameStateStart::update(const float dt)
{
    m_mainMenu.update();


}


void GameStateStart::handleInput()
{
    //Check UI for updates. TODO: replace with signals/slots?
    if(m_mainMenu.getEventExit())
    {
        std::cout << "EVENT EXIT!\n";
        m_mainMenu.clearEventExit();
        m_game->m_window.close();
    }
    else if (m_mainMenu.getEventNewGame())
    {
        std::cout << "EVENT NEW!\n";
        m_mainMenu.clearEventNewGame();
        loadgame();
    }

    sf::Event event;
    while(m_game->m_window.pollEvent(event))
    {
        m_mainMenu.handleEvent(event);


        switch(event.type)
        {
            /* Close the window */
            case sf::Event::Closed:
            {
                std::cout << "Close event!\n";
                m_game->m_window.close();
                break;
            }
            /* Resize the window */
            case sf::Event::Resized:
            {
                resizeWindow(event.size.width, event.size.height);
                break;
            }
            case sf::Event::KeyPressed:
            {
                std::cout << "Key pressed!\n";
                if(event.key.code == sf::Keyboard::Escape)
                {
                    std::cout << "Esc!\n";
                }
                break;
            }

            default: break;
        }
    }

    return;
}

void GameStateStart::resizeWindow(float width, float height)
{
    //could i move this logic to main window, then just always update things based on view size?
    m_mainView.setSize(width, height);
    std::cout << "Resized to " << width << "x" << height << "\n";
    m_game->m_background.setPosition(m_game->m_window.mapPixelToCoords(sf::Vector2i(0, 0)));
    m_game->m_background.setScale(
        width / float(m_game->m_background.getTexture()->getSize().x),
        height / float(m_game->m_background.getTexture()->getSize().y));

    m_mainView.setCenter(width / 2, height / 2);
}
