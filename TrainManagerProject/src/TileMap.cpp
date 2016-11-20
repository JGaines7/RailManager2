#include "TileMap.h"
#include <iostream>
#include <cstdlib>

using namespace tileDefs;

TileMap::TileMap(TextureManager& textureManager):
    m_textureManager(textureManager)
{
    std::cout << "Creating tilemap!" << std::endl;
}

TileMap::~TileMap()
{
    //delete all tile objects

}


bool TileMap::loadTileMapTiles()
{

    return true;
}
bool TileMap::saveTileMapTiles()
{

    return true;
}

bool TileMap::generateTileMap()
{

    std::cout << "gen tilemap!" << std::endl;
    m_width = 5000;
    m_height = 5000;

    //clear and resize TileMap
    m_TileMap.clear();
    m_TileMap.resize(m_width*m_height);

    std::cout << "resized tilemap!" << std::endl;

    for(uint32_t x = 0; x < m_width; x++)
    {
        for(uint32_t y = 0; y < m_height; y++)
        {
            Tile& tile = m_TileMap.at(x + y * m_width);

            uint8_t variant = std::rand() % tileDefs::numGrassColorVariants;
            tile.setTileType(tileDefs::TileTypes::GRASS);
            tile.setTileVariant(variant);
        }
    }

    m_TileMapLoaded = true;

    return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //Dont draw if no map loaded
    if(!m_TileMapLoaded)
    {
        return;
    }

    //Get texture
    sf::Texture texture = m_textureManager.getRef("gridTiles");

    //Calculate the tiles we need to draw based on the view
    sf::Vector2f viewCenter = m_view->getCenter();
    sf::Vector2f viewSize = m_view->getSize();

    float xStart_float = viewCenter.x - viewSize.x / 2.0;
    float yStart_float = viewCenter.y - viewSize.y / 2.0;

    unsigned int xStart_i = std::max(0,static_cast<int>(xStart_float / 32 - 2));
    unsigned int yStart_i = std::max(0,static_cast<int>(yStart_float / 32 - 2));
    unsigned int xEnd_i = std::min(m_width, static_cast<uint32_t>(xStart_i + viewSize.x / 32 + 4));
    unsigned int yEnd_i = std::min(m_height, static_cast<uint32_t>(yStart_i + viewSize.y / 32 + 4));
    unsigned int renderWidth_i = xEnd_i-xStart_i;
    unsigned int renderHeight_i = yEnd_i - yStart_i;

    //Create a vertexArray of the right size
    sf::VertexArray quads;
    quads.setPrimitiveType(sf::Quads);
    quads.resize(renderWidth_i*renderHeight_i * 4);

    //iterate through viewed area of grid and add quads to render.
    for(unsigned int x = 0; x < renderWidth_i; ++x)
    {
        for(unsigned int y = 0; y < renderHeight_i; ++y)
        {
            //add quad
            sf::Vertex* quad = &quads[( x + y * renderWidth_i) * 4];

            //clockwise vertice order from top left
            quad[0] = sf::Vector2f((x + xStart_i) * TILE_SIZE, (y + yStart_i) * TILE_SIZE);
            quad[1] = sf::Vector2f(((x + xStart_i) + 1) * TILE_SIZE, (y + yStart_i) * TILE_SIZE);
            quad[2] = sf::Vector2f(((x + xStart_i) + 1) * TILE_SIZE, ((y + yStart_i) + 1) * TILE_SIZE);
            quad[3] = sf::Vector2f((x + xStart_i) * TILE_SIZE, ((y + yStart_i) + 1) * TILE_SIZE);

            const Tile& currentTile = getTileAtPosition(x + xStart_i, y + yStart_i);
            TileTypes tileType = currentTile.getTileType();
            unsigned int tileVariant = currentTile.getTileVariant();

            //Lookup correct texture offset for tile type/variant
            sf::Vector2u textureOffset(0,0);
            switch(tileType)
            {
                case TileTypes::GRASS:
                {
                    textureOffset = grassOffset * static_cast<unsigned int>(TEXTURE_TILE_SIZE);
                    textureOffset.x += 2;
                    textureOffset.y += 2;
                    textureOffset.x += tileVariant * TEXTURE_TILE_SIZE;
                    break;
                }
                default:
                {
                    textureOffset = grassOffset;
                }
            }

            quad[0].texCoords = sf::Vector2f(textureOffset.x, textureOffset.y);
            quad[1].texCoords = sf::Vector2f((textureOffset.x + TILE_SIZE), textureOffset.y);
            quad[2].texCoords = sf::Vector2f((textureOffset.x + TILE_SIZE), (textureOffset.y + TILE_SIZE));
            quad[3].texCoords = sf::Vector2f(textureOffset.x, (textureOffset.y + TILE_SIZE));
        }
    }
    //draw the vertex array
    states.texture = &texture;
    target.draw(quads, states);



}

