//define tile types and variants
#include <SFML/Graphics.hpp>
#include <stdint.h>

namespace tileDefs{

    enum class TileTypes : uint8_t { GRASS = 0, WATER, DIRT};

    const uint8_t TILE_SIZE = 32; //px
    const uint8_t TEXTURE_TILE_SIZE = 36; //px



    const sf::Vector2u grassOffset(0,0);
    const sf::Vector2u waterOffset(0,1);

    //Grass variant information

    //visual grass color variation will be varied via blending changes
    const uint8_t numGrassColorVariants = 8;
    enum class GrassVariants : uint8_t { }; //needed?

;}
