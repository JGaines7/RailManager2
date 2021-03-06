#include <stack>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "gameState.h"

Game::Game()
{
    //Setup window
    m_window.create(sf::VideoMode(800, 600), "City Builder");
    m_window.setFramerateLimit(60);

    loadTextures();

    m_background.setTexture(m_textureManager.getRef("background"));

    //setup font
    if (!m_font.loadFromFile("arial.ttf"))
	{
		std::cout << "Failed to load font!\n";
	}

}

void Game::pushState(GameState* state)
{
    m_states.push(state);

    return;
}

void Game::popState()
{
    delete m_states.top();
    m_states.pop();

    return;
}

void Game::changeState(GameState* state)
{
    if(!m_states.empty())
        popState();
    pushState(state);

    return;
}

GameState* Game::peekState()
{
    if(m_states.empty()) return nullptr;
    return m_states.top();
}

void Game::gameLoop()
{
    sf::Clock clock;

    while(m_window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        if(peekState() == nullptr) continue;
        peekState()->handleInput();
        peekState()->update(dt);
        m_window.clear(sf::Color::Black);
        peekState()->draw(dt);

        //draw Debug overlay
        drawFps(dt);

        m_window.display();
    }
}



Game::~Game()
{
    while(!m_states.empty()) popState();
}

void Game::drawFps(float dt)
{
    //set view to current gamestate's view
    GameState* state = peekState();
    if(state != nullptr)
    {
       m_window.setView(state->m_mainView);
    }


	char c[10];
	sprintf(c, "%f", 1.0 / dt);
	std::string theString(c);
	sf::String str(theString);
	sf::Text text;
	text.setString(str);
	text.setFillColor(sf::Color::White);
	text.setPosition(5, 5);
	text.setCharacterSize(20);
	text.setFont(m_font);
	m_window.draw(text);
}


void Game::loadTextures()
{
    m_textureManager.loadTexture("background", "media/bg.png");
    m_textureManager.loadTexture("gridTiles", "media/gridTiles.png");
}

