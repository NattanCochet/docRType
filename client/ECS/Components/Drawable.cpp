/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Drawable
*/

#include "Drawable.hpp"

Drawable::Drawable() : _path(), _rect(), _color(), _scale(), _isAnimate(), _kind()
{
}

Drawable::Drawable(std::string path, typeSFML kind, sf::Vector2f scale, sf::IntRect rect, float angle)
{
    if (kind != SPRITE)
        throw Error(Error::MISTAKE::BAD_CONSTRUCTOR);
    _path = path;
    _kind = kind;
    _scale = scale;
    _rect = rect;
    _angle = angle;
}

Drawable::Drawable(std::string fontPath, typeSFML kind, sf::Vector2f scale, std::string message, std::size_t sizeChar, sf::Color color, float angle)
{
    if (kind != TEXT)
        throw Error(Error::MISTAKE::BAD_CONSTRUCTOR);
    if (message == "" || sizeChar == 0)
        throw Error(Error::MISTAKE::MISSING_ARGUMENTS);
    _path = fontPath;
    _kind = kind;
    _scale = scale;
    _message = message;
    _sizeChar = sizeChar;
    _colorText = color;
    _angle = angle;
}

Drawable::Drawable(std::string fontPath, typeSFML kind, sf::Vector2f scale, std::string message, std::size_t sizeChar, sf::Color colorText,
    sf::Color colorBack, sf::Vector2f size, float angle)
{
    if (kind != BUTTON)
        throw Error(Error::MISTAKE::BAD_CONSTRUCTOR);
    _path = fontPath;
    _kind = kind;
    _scale = scale;
    _message = message;
    _sizeChar = sizeChar;
    _colorText = colorText;
    _color = colorBack;
    _size = size;
    _angle = angle;
}

Drawable::~Drawable()
{
}

std::string &Drawable::getPath()
{
    return (this->_path);
}

sf::IntRect *Drawable::getRect()
{
    return &(this->_rect);
}

sf::Color &Drawable::getColorText()
{
    return (this->_colorText);
}

sf::Color &Drawable::getColor()
{
    return (this->_color);
}

sf::Vector2f &Drawable::getScale()
{
    return (this->_scale);
}

bool Drawable::getIsAnimate() const
{
    return (this->_isAnimate);
}

Drawable::typeSFML Drawable::getKind() const
{
    return (_kind);
}

std::string Drawable::getMessage()
{
    return (_message);
}

size_t Drawable::getSizeChar()
{
    return (_sizeChar);
}

sf::Vector2f Drawable::getSizeRectangle()
{
    return (_size);
}

sf::Clock *Drawable::getClock()
{
    return &(_clock);
}

void Drawable::restartClock()
{
    _clock.restart();
}

void Drawable::setPath(std::string newPath)
{
    this->_path = newPath;
}

void Drawable::setRect(sf::IntRect newRect)
{
    this->_rect = newRect;
}

void Drawable::setColorText(sf::Color newTextColor)
{
    this->_colorText = newTextColor;
}

void Drawable::setColor(sf::Color newtColor)
{
    this->_color = newtColor;
}

void Drawable::setScale(sf::Vector2f newScale)
{
    this->_scale = newScale;
}

void Drawable::setIsAnimate(bool newIsAnimate)
{
    this->_isAnimate = newIsAnimate;
}

void Drawable::setMessage(std::string message)
{
    _message = message;
}

void Drawable::setSizeChar(std::size_t sizeChar)
{
    _sizeChar = sizeChar;
}

void Drawable::setSizeRectangle(sf::Vector2f sizeRectangle)
{
    _size = sizeRectangle;
}

float Drawable::getAngle()
{
    return (_angle);
}

void Drawable::setAngle(float newAngle)
{
    _angle = newAngle;
}
