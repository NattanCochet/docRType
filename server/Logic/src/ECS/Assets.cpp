/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Assets
*/

#include "../../include/ECS/Assets.hpp"

Assets::Assets()
{
    LoadSprite("../../assets/background.jpg", {0, 0, 612, 382});
}

Assets::~Assets()
{
}

void Assets::LoadSprite(std::string filepath, std::vector<int> dimensions)
{
    if (dimensions.size() != 4) {
        std::cerr << "Incorrect dimensions data" << std::endl;
        return;
    }

    std::ifstream f(filepath.c_str());

    if (!f.good()) {
        std::cerr << "File " << filepath << " not found" << std::endl;
        return;
    }
    sf::Texture newTexture;

    sf::IntRect newRect(dimensions[0], dimensions[1], dimensions[2], dimensions[3]);
    sf::Sprite newSprite;

    if (!newTexture.loadFromFile(filepath, newRect)) {
        std::cerr << "Error while loading texture from " << filepath << "." << std::endl;
        return;
    }
    newSprite.setTexture(newTexture);
    _list.insert(std::make_pair(filepath, newSprite));
    return;
}

sf::Sprite Assets::getSprite(std::string filePath)
{
    if (!_list.contains(filePath)) {
        throw ErrorKeyNotFound(filePath, "Assets::getSprite");
    }
    return (_list[filePath]);
}
