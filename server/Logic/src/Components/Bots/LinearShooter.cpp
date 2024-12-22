/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** LinearShooter
*/

#include "../../../include/Components/Bots/LinearShooter.hpp"

LinearShooter::LinearShooter(float delay, bool honrizontal)
{
    _delay = delay;
    _honrizontal = honrizontal;
}

LinearShooter::LinearShooter(float delay)
{
    _delay = delay;
    _honrizontal = false;
}

LinearShooter::LinearShooter()
{
    _delay = 2;
    _honrizontal = false;
}

bool LinearShooter::isHonrizontal()
{
    return _honrizontal;
}