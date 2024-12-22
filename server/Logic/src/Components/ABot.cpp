/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ABot
*/

#include "../../include/Components/ABot.hpp"

float ABot::getDelay(void)
{
    return _delay;
}

sf::Clock &ABot::getClock(void)
{
    return _clock;
}
