#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
class FpsManager
{
public:
	FpsManager(sf::RenderWindow &window);
	~FpsManager();
	void updateFps();
	void drawFps();

private:

	sf::Clock m_clock;
	float m_fps = 0;
	sf::RenderWindow& m_window;
	//font while we dont have resource manager
	sf::Font m_font;
};

