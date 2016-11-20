#include "UI_MainMenu.h"
#include <iostream>

UI_MainMenu::UI_MainMenu()
{
    //ctor
}

UI_MainMenu::~UI_MainMenu()
{
    //dtor
}


void UI_MainMenu::update()
{
    //draw sample window
    //ImGui::SetNextWindowSize(sf::Vector2f(300,400));
    ImGui::SetNextWindowPosCenter(true);
    ImGuiWindowFlags flags =    ImGuiWindowFlags_NoMove |
                                ImGuiWindowFlags_NoCollapse |
                                ImGuiWindowFlags_NoTitleBar |
                                ImGuiWindowFlags_AlwaysAutoResize;

    //flags for main menu window



    ImGui::Begin("Main Menu", NULL, flags); // begin window

    if (ImGui::Button("Start Game", sf::Vector2f(280,50))) {

        std::cout << "Start Game\n";
        m_eventNewGame = true;
    }
    if (ImGui::Button("Load Game", sf::Vector2f(280,50))) {

        std::cout << "Load Game\n";
    }
    if (ImGui::Button("Settings", sf::Vector2f(280,50))) {

        std::cout << "Settings\n";
    }
    if (ImGui::Button("Exit Game", sf::Vector2f(280,50))) {

        std::cout << "Exit Game\n";
        m_eventExit = true;

    }
    ImGui::Checkbox("Show Demo UI", &m_show_demo_ui);


    if(m_show_demo_ui)
    {
        ImGui::ShowTestWindow();
    }

    ImGui::End(); // end window
}


void UI_MainMenu::handleEvent(sf::Event event)
{
    ImGui::SFML::ProcessEvent(event);

}
