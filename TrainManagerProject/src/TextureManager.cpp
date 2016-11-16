#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>

#include "TextureManager.h"

//Load texture file from path
void TextureManager::loadTexture(const std::string& name, const std::string& filename)
{

    /* Load the texture */
    sf::Texture tex;
    std::cout << tex.getMaximumSize() << "\n";
    tex.loadFromFile(filename);

    /* Add it to the list of textures */
    m_textures[name] = tex;

    return;
}

//get texture reference of a loaded reference
sf::Texture& TextureManager::getRef(const std::string& texture)
{
    return m_textures.at(texture);
}
