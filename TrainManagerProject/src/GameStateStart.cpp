#include "GameStateStart.h"

#include "GameStateWorld.h"
#include "GameState.h"
#include <iostream>


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
    m_game->m_window.draw(m_game->m_background);

    //Draw main menu using sfgui

    //Placeholder main menu to know it's working

	sf::String str("Press Space to start game.\nRight click+drag to pan.");
	sf::Text text;
	text.setString(str);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(20);
	text.setFont(m_game->m_font);
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top + textRect.height/2.0f);

	text.setPosition(m_game->m_window.getSize().x / 2, m_game->m_window.getSize().y / 2);

	m_game->m_window.draw(text);

	//m_testUI.draw();

    return;
}

void GameStateStart::update(const float dt)
{
    //m_testUI.update(dt);
}


void GameStateStart::handleInput()
{
    sf::Event event;

    while(m_game->m_window.pollEvent(event))
    {
//        m_testUI.handleEvent(event);

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
                //could i move this logic to main window, then just always update things based on view size?
                m_mainView.setSize(event.size.width, event.size.height);
                std::cout << "Resized to " << event.size.width << "x" << event.size.height << "\n";
                m_game->m_background.setPosition(m_game->m_window.mapPixelToCoords(sf::Vector2i(0, 0)));
                m_game->m_background.setScale(
                    float(event.size.width) / float(m_game->m_background.getTexture()->getSize().x),
                    float(event.size.height) / float(m_game->m_background.getTexture()->getSize().y));

                m_mainView.setCenter(event.size.width / 2, event.size.height / 2);
                break;
            }
            case sf::Event::KeyPressed:
            {
                std::cout << "Key pressed!\n";
                if(event.key.code == sf::Keyboard::Escape)
                {
                    std::cout << "Esc!\n";
                    m_game->m_window.close();
                }
                else if(event.key.code == sf::Keyboard::Space)
                {
                    std::cout << "Spva!\n";
                    loadgame();
                }
                break;
            }

            default: break;
        }
    }

    return;
}
