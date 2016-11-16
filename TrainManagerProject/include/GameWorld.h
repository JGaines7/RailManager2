#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "Game.h"

//Class that holds all world information, including objects, money, etc.
class GameWorld : public sf::Drawable
{
    public:
        GameWorld(Game* game);
        virtual ~GameWorld();

        bool loadGame(std::string fileName);
        bool saveGame(std::string fileName);


        void setView(std::shared_ptr<sf::View> view) { m_view = view; m_tileMap.setView(view);}

        //probably move to terrain generator class later on, and always load maps.
        bool generateRandomMap();

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:

        Game* m_game;

        std::shared_ptr<sf::View> m_view;

        //properties of a world file.
        uint32_t m_date = 0;
        uint32_t m_money = 0;
        //trainmanager, station manager, depo manager, tilemap, objectmap, etc.
        TileMap m_tileMap;



};

#endif // GAMEWORLD_H
