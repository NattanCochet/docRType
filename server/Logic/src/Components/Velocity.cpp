/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Velocity
*/

#include "../../include/Components/Velocity.hpp"

Velocity::Velocity(sf::Vector2i speed, float seconds, float coeff)
    : _speed(speed), _seconds(seconds), _coeff(coeff)
{
}

Velocity::Velocity(int xSpeed, int ySpeed, float seconds, float coeff)
    : _seconds(seconds), _coeff(coeff)
{
    _speed = sf::Vector2i(xSpeed, ySpeed);
}

Velocity::Velocity() : _speed(), _seconds(), _coeff()
{
}

Velocity::~Velocity()
{
}

sf::Vector2i &Velocity::getSpeed()
{
    return (this->_speed);
}

float &Velocity::getSeconds()
{
    return (this->_seconds);
}

float &Velocity::getCoeff()
{
    return (this->_coeff);
}

void Velocity::setSpeed(sf::Vector2i newSpeed)
{
    this->_speed = newSpeed;
}

void Velocity::setSpeed(int newXSpeed, int newYSpeed)
{
    this->_speed = sf::Vector2i(newXSpeed, newYSpeed);
}

void Velocity::setSeconds(float newSeconds)
{
    this->_seconds = newSeconds;
}

void Velocity::setCoeff(float newCoeff)
{
    this->_coeff = newCoeff;
}
