/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Clock
*/

#include "../../include/Components/Clock.hpp"

Clock::Clock()
{
}

Clock::~Clock()
{
}

void Clock::addClock(const std::string &idClock)
{
    if (_mapClock.contains(idClock)) {
        throw ErrorKeyAlreadyExistInMap(idClock, "Clock::addClock");
    }
    _mapClock[idClock] = sf::Clock();
}

sf::Clock &Clock::getClock(const std::string &idClock)
{
    if (!_mapClock.contains(idClock)) {
        throw ErrorKeyNotFound(idClock, "Clock::getClock");
    }
    return (_mapClock[idClock]);
}
