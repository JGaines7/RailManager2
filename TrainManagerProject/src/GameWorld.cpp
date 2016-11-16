#include "GameWorld.h"

GameWorld::GameWorld(Game* game):
     m_tileMap(game->getTextureManager())
{

    //ctor
}

GameWorld::~GameWorld()
{
    //dtor
}

bool GameWorld::saveGame(std::string fileName)
{
    m_tileMap.saveTileMapTiles();
    return true;
}

bool GameWorld::loadGame(std::string fileName)
{
    m_tileMap.loadTileMapTiles();
    return true;
}

bool GameWorld::generateRandomMap()
{

    return m_tileMap.generateTileMap();
}

void GameWorld::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    m_tileMap.draw(target, states);
}
