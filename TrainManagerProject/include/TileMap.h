#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "TextureManager.h"
#include <vector>


//Simple 2d map of tiles to manage creation and deletion.
//Any advanced logic is managed by the GameState_World class

//Question: Will i lose efficiency if I do iteration over several
//          get calls, vs logic directly in this class?
class TileMap : public sf::Drawable
{
    public:
        TileMap(TextureManager& textureManager);
        virtual ~TileMap();
        //return constant reference to a tile
        const Tile& getTileAtPosition(uint32_t x, uint32_t y) const { return m_TileMap.at(x + y*m_width);}
        //return r/w reference to tile  Only use if necessary.
        Tile& getTileAtPostion_rw(uint32_t x, uint32_t y)  {return m_TileMap.at(x + y*m_width);}

        //has the TileMap been initialized
        const bool isLoaded() const {return m_TileMapLoaded;}

        //load and save TileMap to binary buffer
        bool loadTileMapTiles();
        bool saveTileMapTiles();

        void setView(std::shared_ptr<sf::View> view) { m_view = view;}

        //generate a new TileMap with a given TileMap generator object
        bool generateTileMap(); //for now placeholder TileMap generation
        //bool generateTileMap(TileMapGenerator TileMapGenerator)

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


    private:

        sf::Clock clock;

        std::shared_ptr<sf::View> m_view;
        std::vector<Tile> m_TileMap;
        bool m_TileMapLoaded = false;
        uint32_t m_width;
        uint32_t m_height;
        TextureManager& m_textureManager;
};

#endif // MAP_H
