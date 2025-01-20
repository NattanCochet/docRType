/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Asset
*/

#include "Assets.hpp"

Assets::Assets()
{
    std::string path = PATH;

    loadSprite(std::string(path) + "client/Assets/background.png", sf::IntRect(), "background", {2.5, 2.5});
    loadSprite(std::string(path) + "client/Assets/players_sking.png", sf::IntRect(), "Player", {2.5, 2.5});
    loadSprite(std::string(path) + "client/Assets/explosion.png", sf::IntRect(), "explosion", {1, 1});
    loadSprite(std::string(path) + "client/Assets/lock.png", sf::IntRect(), "lock", {1, 1});
    loadSprite(std::string(path) + "client/Assets/force_lvl_1.png", sf::IntRect(), "Force1", {1, 1});
    loadSprite(std::string(path) + "client/Assets/force_lvl_2_right.png", sf::IntRect(), "forceRightLVL2", {1, 1});
    loadSprite(std::string(path) + "client/Assets/force_lvl_2_left.png", sf::IntRect(), "forceLeftLVL2", {1, 1});
    loadSprite(std::string(path) + "client/Assets/force_lvl_3_right.png", sf::IntRect(), "forceRightLVL3", {1, 1});
    loadSprite(std::string(path) + "client/Assets/force_lvl_3_left.png", sf::IntRect(), "forceLeftLVL3", {1, 1});
    loadSprite(std::string(path) + "client/Assets/SinusoidalShooter.png", sf::IntRect(), "SS", {1, 1});
    loadSprite(std::string(path) + "client/Assets/TPShooter.png", sf::IntRect(), "TP", {1, 1});
    loadSprite(
        std::string(path) + "client/Assets/LinearShooterVertical.png", sf::IntRect(), "LSH", {1, 1});
    loadSprite(std::string(path) + "client/Assets/LinearShooterHorizontal.png", sf::IntRect(),
        "LSV", {1, 1});
    loadSprite(std::string(path) + "client/Assets/kamikaze.png", sf::IntRect(), "KS", {1, 1});
    loadSprite(std::string(path) + "client/Assets/player_shoot.png", sf::IntRect(), "PS", {1, 1});
    loadSprite(
        std::string(path) + "client/Assets/player_charged_shoot.png", sf::IntRect(), "BE", {1, 1});
    loadSprite(std::string(path) + "client/Assets/ennemi_shoot.png", sf::IntRect(), "ES", {1, 1});
    loadSprite(std::string(path) + "client/Assets/ennemi_laser_shoot.png", sf::IntRect(), "EBL", {1, 1});
    loadSprite(
        std::string(path) + "client/Assets/force_shoot_lvl_1_right.png", sf::IntRect(), "FS1R", {1, 1});
    loadSprite(
        std::string(path) + "client/Assets/force_shoot_lvl_1_left.png", sf::IntRect(), "FS1L", {1, 1});
    loadSprite(
        std::string(path) + "client/Assets/force_shoot_lvl_2_right.png", sf::IntRect(), "FS2R", {1, 1});
    loadSprite(
        std::string(path) + "client/Assets/force_shoot_lvl_2_left.png", sf::IntRect(), "FS2L", {1, 1});
    loadSprite(std::string(path) + "client/Assets/force_shoot_lvl_2_right_top.png", sf::IntRect(),
        "FS2RT", {1, 1});
    loadSprite(std::string(path) + "client/Assets/force_shoot_lvl_2_left_top.png", sf::IntRect(),
        "FS2LT", {1, 1});
    loadSprite(std::string(path) + "client/Assets/force_shoot_lvl_2_right_bottom.png", sf::IntRect(),
        "FS2RB", {1, 1});
    loadSprite(std::string(path) + "client/Assets/force_shoot_lvl_2_left_bottom.png", sf::IntRect(),
        "FS2LB", {1, 1});
    loadSprite(
        std::string(path) + "client/Assets/force_shoot_lvl_3_right.png", sf::IntRect(), "FS3R", {1, 1});
    loadSprite(
        std::string(path) + "client/Assets/force_shoot_lvl_3_left.png", sf::IntRect(), "FS3L", {1, 1});
    loadSprite(std::string(path) + "client/Assets/bomb.png", sf::IntRect(), "BB", {1, 1});
    loadSprite(std::string(path) + "client/Assets/asteroid.png", sf::IntRect(), "D", {1, 1});
    loadSprite(std::string(path) + "client/Assets/speed_bonus.png", sf::IntRect(), "BS", {1, 1});
    loadSprite(std::string(path) + "client/Assets/force_bonus.png", sf::IntRect(), "BF", {1, 1});
    loadSprite(std::string(path) + "client/Assets/star_bonus.png", sf::IntRect(), "BST", {1, 1});
    loadSprite(std::string(path) + "client/Assets/life_bonus.png", sf::IntRect(), "BOU", {1, 1});
    loadSprite(std::string(path) + "client/Assets/missile.png", sf::IntRect(), "B", {1, 1});
    loadSprite(std::string(path) + "client/Assets/sprite_first_boss.png", sf::IntRect(), "AlienEmperor", {1, 1});
    loadSprite(std::string(path) + "client/Assets/sprite_second_boss.png", sf::IntRect(), "SpatialDustman", {1, 1});
    loadSprite(std::string(path) + "client/Assets/sprite_third_boss.png", sf::IntRect(), "BigShip", {1, 1});
    loadText(std::string(path) + "client/Assets/RegularRoboto.ttf", "robotoTTF");
    loadText(std::string(path) + "client/Assets/Title_Menu.ttf", "titleMenuTTF");
    loadText(std::string(path) + "client/Assets/Arrows.ttf", "arrowsTTF");
    loadRectangle();
}

Assets::~Assets()
{
}

void Assets::loadSprite(std::string filepath, sf::IntRect rect, std::string name, sf::Vector2f scale)
{
    sf::Texture *texture = new sf::Texture();
    sf::Sprite sprite;
    if (texture->loadFromFile(filepath, rect) == false)
        throw Error(Error::MISTAKE::SPRITE_ERROR);
    sprite.setTexture(*texture);
    sf::FloatRect middle = sprite.getLocalBounds();
    sprite.setOrigin(middle.width / 2, middle.height / 2);
    sprite.setScale(scale);
    _mapSprites.insert(std::make_pair(name, sprite));
}

void Assets::loadText(std::string filepath, std::string name)
{
    sf::Font *textFont = new sf::Font();
    if (textFont->loadFromFile(filepath) == false)
        throw Error(Error::MISTAKE::FONT_ERROR);
    sf::Text text("", *textFont, 0);
    _mapTexts.insert(std::make_pair(name, text));
}

void Assets::loadRectangle()
{
    sf::RectangleShape rectangle;
    _mapRectangle.insert(std::make_pair("rectangle", rectangle));
}

sf::Sprite *Assets::getSprite(std::string name)
{
    if (!_mapSprites.contains(name)) {
        std::cout << name << std::endl;
        // throw Error(Error::MISTAKE::SPRITE_NOT_FOUND);
    }
    return &(_mapSprites[name]);
}

sf::Text *Assets::getText(std::string name)
{
    if (!_mapTexts.contains(name)) {
        std::cout << name << std::endl;
        throw Error(Error::MISTAKE::TEXT_NOT_FOUND);
    }
    return &(_mapTexts[name]);
}

sf::RectangleShape *Assets::getRectangle(std::string name)
{
    if (!_mapRectangle.contains(name)) {
        throw Error(Error::MISTAKE::RECTANGLE_NOT_FOUND);
    }
    return &(_mapRectangle[name]);
}
