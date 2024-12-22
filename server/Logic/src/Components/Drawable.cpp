/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Drawable
*/

#include "../../include/Components/Drawable.hpp"

Drawable::Drawable(std::string path, Vector<float, 4> rect, bool isAnimated, sf::Vector2f scale, bool player,
        std::vector<int> frameUp, std::vector<int>frameDown, std::vector<int>frameLeft, std::vector<int>frameRight)
{
    _path = path;
    _rect = rect;
    _isAnimated = isAnimated;
    _scale = scale;
    _player = player;
    _frameUp = frameUp;
    _frameDown = frameDown;
    _frameLeft = frameLeft;
    _frameRight = frameRight;
}

Drawable::~Drawable()
{
}

std::string &Drawable::getPath()
{
    return (this->_path);
}

Vector<float, 4> &Drawable::getRect()
{
    return (this->_rect);
}

sf::Vector2f &Drawable::getScale()
{
    return (this->_scale);
}

bool Drawable::getIsAnimate() const
{
    return (this->_isAnimated);
}

bool Drawable::isPlayer() const
{
    return (this->_player);
}

sf::IntRect Drawable::getTextRect()
{
    return (this->_textRect);
}

std::vector<int> Drawable::getFrameUp()
{
    return _frameUp;
}

std::vector<int> Drawable::getFrameDown()
{
    return _frameDown;
}

std::vector<int> Drawable::getFrameLeft()
{
    return _frameLeft;
}

std::vector<int> Drawable::getFrameRight()
{
    return _frameRight;
}

void Drawable::setPath(std::string newPath)
{
    this->_path = newPath;
}

void Drawable::setRect(Vector<float, 4> newRect)
{
    this->_rect = newRect;
}

void Drawable::setScale(sf::Vector2f newScale)
{
    this->_scale = newScale;
}

void Drawable::setIsAnimate(bool newIsAnimate)
{
    this->_isAnimated = newIsAnimate;
}

void Drawable::setPlayer(bool newPlayer)
{
    this->_player = newPlayer;
}

void Drawable::setTextRect(sf::IntRect newTextRect)
{
    this->_textRect = newTextRect;
}

void Drawable::setFrameUp(std::vector<int> newFrameUp)
{
    this->_frameUp = newFrameUp;
}

void Drawable::setFrameDown(std::vector<int> newFrameDown)
{
    this->_frameDown = newFrameDown;
}

void Drawable::setFrameLeft(std::vector<int> newFrameLeft)
{
    this->_frameLeft = newFrameLeft;
}

void Drawable::setFrameRight(std::vector<int> newFrameRight)
{
    this->_frameRight = newFrameRight;
}
