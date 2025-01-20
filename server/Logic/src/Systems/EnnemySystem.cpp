/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** EnnemySystem
*/

#include "../../include/Systems.hpp"


int Systems::ennemySystem(World &world, NetworkServer &server)
{
    Registry &r = world.getRegistry();

    ComponentArray<Ennemy> &ennemies = r.get_components<Ennemy>();
    ComponentArray<Position> &position = r.get_components<Position>();

    std::size_t index = 0;

    std::size_t maxIndex = std::min({ennemies.size(), position.size()});


    for (index; index != maxIndex; index++) {
        if (ennemies[index] && ennemies[index].has_value() && position[index] && position[index].has_value()) {
            std::shared_ptr<ABot> bot = ennemies[index]->getBot();
            sf::Clock &clock = bot->getClock();
            bot->moveBot(world, index);
            if (clock.getElapsedTime().asSeconds() >= bot->getDelay()) {
                bot->shootProjectile(world, index);
                clock.restart();
            }
        }
    }

    return 0;
}
