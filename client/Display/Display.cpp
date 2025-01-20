/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Display
*/

#include "Display.hpp"

Display::Display(sf::RenderWindow *window)
{
    _window = window;
}

Display::~Display()
{
}

void Display::displaySprite(std::string name, std::string path, sf::Vector2f position, sf::Vector2f scale, float animationSecond)
{
    sf::Texture texture;
    if (texture.loadFromFile(path) == false)
        throw Error(Error::MISTAKE::SPRITE_ERROR);
    sf::Sprite sprite(texture);
    sf::FloatRect middle = sprite.getLocalBounds();
    sprite.setOrigin(middle.width / 2, middle.height / 2);
    sprite.setPosition(position);
    sprite.setScale(scale);
    _window->draw(sprite);
}

void Display::displayText(std::string message, std::string fontPath, int sizeChar, sf::Color color,
        sf::Vector2f position)
{
    sf::Font textFont;
    if (textFont.loadFromFile(fontPath) == false)
        throw Error(Error::MISTAKE::FONT_ERROR);
    sf::Text text(message, textFont, sizeChar);
    sf::FloatRect middle = text.getLocalBounds();
    text.setOrigin(middle.width / 2, middle.height / 2);
    text.setPosition(position);
    text.setFillColor(color);
    _window->draw(text);
}

void Display::displayRectangle(sf::Color color, sf::Vector2f position, sf::Vector2f size)
{
    sf::RectangleShape rectangle;
    rectangle.setOrigin(size.x / 2, size.y / 2);
    rectangle.setSize(size);
    rectangle.setFillColor(color);
    rectangle.setPosition(position);
    _window->draw(rectangle);
}

void Display::displayButton(std::string message, std::string fontPath, int sizeChar, sf::Color colorText,
        sf::Color colorBack, sf::Vector2f position, sf::Vector2f size, std::function<void()> function)
{
    displayRectangle(colorBack, position, size);
    displayText(message, fontPath, sizeChar, colorText, position);
    sf::Rect<float> rect((position.x - (size.x / 2)), (position.y - (size.y / 2)), size.x, size.y);
    _buttons.push_front({rect, function});
}

void Display::clearButtons()
{
    _buttons.clear();
}

std::list<std::pair<sf::Rect<float>, std::function<void()>>> Display::getButtons()
{
    return (_buttons);
}
