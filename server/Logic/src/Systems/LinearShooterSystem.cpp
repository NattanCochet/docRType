/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** LinearShooterSystem
*/

#include "../../include/Systems.hpp"

int Systems::linearSystem(World &world)
{
    auto &r = world.getRegistry();

    ComponentArray<Velocity> &velocity = r.get_components<Velocity>();
    ComponentArray<Position> &position = r.get_components<Position>();
    ComponentArray<LinearShooter> &linear = r.get_components<LinearShooter>();

    std::size_t index = 0;

    if (velocity.size() != 0 && position.size() != 0 && linear.size() != 0) {
        for (auto &l : linear) {
            if (l && l.has_value()
                && position[index] && position[index].has_value()
                && velocity[index] && velocity[index].has_value()
            ) {
                auto &posAct = position[index];
                auto &velAct = velocity[index];

                sf::Vector2f &coordsAct = posAct->getPosition();
                sf::Vector2i &speedAct = velAct->getSpeed();
                sf::Clock &clockAct = l->getClock();

                if ((coordsAct.y >= 800 || coordsAct.y <= 0) || (coordsAct.x >= 1000 || coordsAct.x <= 0))  {
                    velAct->setSpeed(-speedAct.x, -speedAct.y);
                }

                //std::cout << clockAct.getElapsedTime().asSeconds() << " " << l->getDelay() << std::endl;

                if (clockAct.getElapsedTime().asSeconds() >= l->getDelay()) {
                    auto laser = r.spawn_entity();
                    if (l->isHonrizontal()) {
                        r.add_component(laser, Velocity(sf::Vector2i(-9, 0), 0.0, 0.0));
                    } else {
                        r.add_component(laser, Velocity(sf::Vector2i(0, 9), 0.0, 0.0));
                    }
                    r.add_component(laser, Position(coordsAct.x, coordsAct.y));
                    r.add_component(laser, Projectile(20.0f, 0.6f, false, false, 0.0f, 0.4f));
                    clockAct.restart();
                }

            }
            index++;
        }
    }

    return (0);
}