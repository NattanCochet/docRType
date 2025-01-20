/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** VelocitySystem
*/

#include "../../include/Systems.hpp"

int Systems::velocitySystem(World &world, NetworkServer &server)
{
    Registry &r = world.getRegistry();
    ComponentArray<Velocity> &velocity = r.get_components<Velocity>();
    ComponentArray<Position> &position = r.get_components<Position>();

    std::size_t index = 0;

    for (auto &i : velocity) {
        if (i && i.has_value()) {
            sf::Time elapsedTime = world.getClock().getElapsedTime();
            if (elapsedTime.asSeconds() > i->getSeconds()) {
                sf::Vector2f &pos = position[index]->getPosition();
                const sf::Vector2i &speed = i->getSpeed();
                pos.x += speed.x;
                pos.y += speed.y;
                i->setSeconds(i->getSeconds() += i->getCoeff());
            }
        }
        index++;
    }
    return (0);
}
