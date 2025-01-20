/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** SinusoidalShooter
*/

#include "../../../include/Components/Bots/SinusoidalShooter.hpp"
#include <cmath>

#ifdef _WIN32
#define M_PI 3.14159265358979323846
#endif

SinusoidalShooter::SinusoidalShooter(float delay, float amplitude, float frequency, float vSpeed)
{
    _delay = delay;
    _amplitude = amplitude;
    _frequency = frequency;
    _vSpeed = vSpeed;
    _phase = 0.0f;
}

void SinusoidalShooter::moveBot(World &world, std::size_t myIndexEntity)
{
    std::optional<Position> &pos = world.getRegistry().get_components<Position>()[myIndexEntity];

    if (!pos || !pos.has_value()) {
        return;
    }

    sf::Vector2f &coords = pos->getPosition();

    _phase += _vSpeed * 0.01;
    coords.y += _amplitude * std::sin(2 * M_PI * _frequency * _phase);
}

void SinusoidalShooter::shootProjectile(World &world, std::size_t myIndexEntity)
{
    std::optional<Position> &pos = world.getRegistry().get_components<Position>()[myIndexEntity];

    if (!pos || !pos.has_value() || !pos->getIsAppearOnTheWindow()) {
        return;
    }

    world.getClassCreateEntity().createShootEnnemy(pos->getPosition(), world.getRegistry(), myIndexEntity);
}
