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

void AlienEmperor::moveBot(World &world, std::size_t myIndexEntity)
{
    Registry &r = world.getRegistry();
    std::optional<Position> &pos = r.get_components<Position>()[myIndexEntity];
    std::optional<Velocity> &vel = r.get_components<Velocity>()[myIndexEntity];

    if (!pos.has_value() || !vel.has_value()) {
        return;
    }
    if (pos->getPosition().x <= 1200) {
        r.remove_component<Velocity>(r.entity_from_index(myIndexEntity));
    }
}

void AlienEmperor::shootProjectile(World &world, std::size_t myIndexEntity)
{
    CreateEntity &ce = world.getClassCreateEntity();
    Registry &r = world.getRegistry();
    std::optional<Position> &pos = r.get_components<Position>()[myIndexEntity];
    std::optional<Velocity> &vel = r.get_components<Velocity>()[myIndexEntity];

    if (!pos.has_value() || vel.has_value()) {
        return;
    }

    std::optional<Drawable::Drawable> &drawables = r.get_components<Drawable::Drawable>()[myIndexEntity];

    if (_shipSpawn.getElapsedTime().asSeconds() >= _delayShip) {
        ce.createLinearShooterHorizontal(sf::Vector2f(pos->getPosition().x + 100, pos->getPosition().y + 250), r);
        _shipSpawn.restart();
    }

    if (drawables->getCurrentFrame() > 3) {
        ce.createShootEnnemy(sf::Vector2f(pos->getPosition().x + 350, pos->getPosition().y + 420), r, myIndexEntity);
    }
}
