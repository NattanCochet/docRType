/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Position
*/

#include "../../include/Components/Position.hpp"

Position::Position() : _pos()
{
}

Position::Position(sf::Vector2f pos) : _pos(pos), _defaultPos(pos)
{
}

Position::Position(int x, int y)
{
    this->_pos = sf::Vector2f(x, y);
    this->_defaultPos = _pos;
}

Position::~Position()
{
}

sf::Vector2f &Position::getPosition()
{
    return (this->_pos);
}

sf::Vector2f &Position::getDefaultPosition()
{
    return (this->_defaultPos);
}

void Position::setPosition(sf::Vector2f newPos)
{
    this->_pos = newPos;
}

void Position::setPosition(int x, int y)
{
    this->_pos = sf::Vector2f(x, y);
}

void Position::setDefaultPosition(sf::Vector2f newPos)
{
    this->_defaultPos = newPos;
}

void Position::setDefaultPosition(int x, int y)
{
    this->_defaultPos = sf::Vector2f(x, y);
}
