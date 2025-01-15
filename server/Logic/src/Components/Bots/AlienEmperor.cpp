/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris [WSL: Ubuntu-22.04]
** File description:
** AlienEmperor
*/

#include "../../../include/Components/Bots/AlienEmperor.hpp"

AlienEmperor::AlienEmperor(float delay, float delay2)
{
    _delay = delay;
    _delayShip = delay2;
}

AlienEmperor::~AlienEmperor()
{
}

void AlienEmperor::shootProjectile(World &world, std::size_t myIndexEntity)
{
    CreateEntity &ce = world.getClassCreateEntity();
    std::optional<Position> &pos = world.getRegistry().get_components<Position>()[myIndexEntity];
    std::optional<Drawable::Drawable> &drawables = world.getRegistry().get_components<Drawable::Drawable>()[myIndexEntity];

    if (_shipSpawn.getElapsedTime().asSeconds() >= _delayShip) {
        ce.createLinearShooterHorizontal(sf::Vector2f(pos->getPosition().x + 100, pos->getPosition().y + 250), world.getRegistry());
        _shipSpawn.restart();
    }

    if (drawables->getCurrentFrame() > 3) {
        ce.createLaser(sf::Vector2f(pos->getPosition().x + 350, pos->getPosition().y + 420), world.getRegistry(), myIndexEntity, false, false);
    }
}
