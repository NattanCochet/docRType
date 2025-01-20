/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** PlayerAI
*/

#include "../../include/Components/PlayerAI.hpp"

PlayerAI::PlayerAI()
{
}

PlayerAI::~PlayerAI()
{
}

float PlayerAI::getDelay()
{
    return _delay;
}

sf::Clock &PlayerAI::getMoveClock()
{
    return _move;
}

float PlayerAI::getShootDelay()
{
    return _shootDelay;
}

sf::Clock &PlayerAI::getShootClock()
{
    return _shoot;
}

int PlayerAI::getStacks()
{
    return _stacks;
}

void PlayerAI::setStacks(int newStacks)
{
    _stacks = newStacks;
}

float PlayerAI::getBigShootDelay()
{
    return _bigShootDelay;
}

sf::Clock &PlayerAI::getBigShoot()
{
    return _bigShoot;
}
