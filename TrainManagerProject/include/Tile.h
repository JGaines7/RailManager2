#ifndef TILE_H
#define TILE_H

#include <stdint.h>
#include <array>
#include <memory>
#include "TextureManager.h"
#include "TileDefinitions.h"

class Tile
{
    public:
        Tile();
        virtual ~Tile();

        const tileDefs::TileTypes getTileType() const {return m_tileType;}
        void setTileType(tileDefs::TileTypes tileType) {m_tileType = tileType;}

        const uint8_t getTileVariant() const {return m_tileVariant;}
        void setTileVariant(uint8_t variant) {m_tileVariant = variant;}

    private:

        //Tile Type Enum
        tileDefs::TileTypes m_tileType = tileDefs::TileTypes::GRASS; //Possible examples: nodraw, grass, dirt, water, mountain, trees,

        //Tile variant. Meaning is dependent on tile type so not a strict enum class.
        uint8_t m_tileVariant = 0;

};

#endif // TILE_H
