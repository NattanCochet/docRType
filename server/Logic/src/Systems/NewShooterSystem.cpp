/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** NewShooterSystem
*/

#include "../../include/Systems.hpp"

#include <boost/random.hpp>

int Systems::NewShooterSystem(World &world)
{
    static boost::random::mt19937 rng;
    static boost::random::uniform_int_distribution<> x_dist(20, 900);
    static boost::random::uniform_int_distribution<> y_dist(20, 700);

    auto &r = world.getRegistry();
    ComponentArray<Position> &position = r.get_components<Position>();
    ComponentArray<NewShooter> &new_shooters = r.get_components<NewShooter>();

    std::size_t index = 0;

    if (position.size() != 0 && new_shooters.size() != 0) {
        for (auto &ns : new_shooters) {
            if (ns && ns.has_value()
                && position[index] && position[index].has_value()
            ) {
                auto &posAct = position[index];
                sf::Vector2f &coordsAct = posAct->getPosition();
                sf::Clock &clockAct = ns->getClock();

                if (clockAct.getElapsedTime().asSeconds() >= ns->getDelay()) {
                    auto laser = r.spawn_entity();
                    r.add_component(laser, Velocity(sf::Vector2i(-9, 0), 0.0, 0.0));
                    r.add_component(laser, Position(coordsAct.x, coordsAct.y));
                    r.add_component(laser, Projectile(20.0f, 0.6f, false, false, 0.0f, 0.4f));
                    int new_x = x_dist(rng);
                    int new_y = y_dist(rng);
                    posAct->setPosition(new_x, new_y);
                    clockAct.restart();
                }
            }
            index++;
        }
    }
    return 0;
}