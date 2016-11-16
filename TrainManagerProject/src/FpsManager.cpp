#include "FpsManager.h"

FpsManager::FpsManager(sf::RenderWindow & window) :
	m_window(window)
{
	//pass reference to a 'resource manager' class? to get fonts and shit
	std::cout << "Initialized FPS manager\n";

	if (!m_font.loadFromFile("arial.ttf"))
	{
		std::cout << "Failed to load font!\n";
	}

}

FpsManager::~FpsManager()
{
}

void FpsManager::updateFps()
{
	float elapsedTime = m_clock.restart().asSeconds();
	m_fps = 1.0 / elapsedTime;
}

void FpsManager::drawFps()
{
	char c[10];
	sprintf(c, "%f", m_fps);
	std::string string(c);
	sf::String str(string);
	sf::Text text;
	text.setString(str);
	text.setFillColor(sf::Color::White);
	text.setPosition(5, 5);
	text.setCharacterSize(20);
	text.setFont(m_font);
	m_window.draw(text);
}
