#ifndef UI_MAINMENU_H
#define UI_MAINMENU_H

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "imgui.h"
#include "imgui-sfml.h"


//the GAME object will handle the overall imgui reset
//event handling will occur in the active gamestate's event handle loop.
//imgui global draw will happen at the end of game object's draw function.
//TODO: How do we handle sending commands from UI to the game?  signals?

//JORDAN: for now just get this working with a cout

class UI_MainMenu
{
    public:
        UI_MainMenu();
        virtual ~UI_MainMenu();

        void update();
        void handleEvent(sf::Event event);

        const bool getEventExit() const {return m_eventExit;}
        const bool getEventNewGame() const {return m_eventNewGame;}

        void clearEventExit() { m_eventExit = false;}
        void clearEventNewGame()  { m_eventNewGame = false;}

    protected:

    private:

    bool m_show_demo_ui = false;
    bool m_eventNewGame = false;
    bool m_eventExit = false;
    Game* m_game;
};

#endif // UI_MAINMENU_H
