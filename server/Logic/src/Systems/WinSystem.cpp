/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** WinSystem
*/

#include "../../include/Systems.hpp"

int Systems::winSystem(World &world, NetworkServer &server)
{
    if (!world.getIsLevelFinishedToSpawn()) {
        return (0);
    }
    MyClock &clockGenrationWorld = world.getClockGenerationWorld();
    if (clockGenrationWorld.getElapsedTime().asSeconds() < world.getSpawnTimeThreshold()) {
        return (0);
    }
    ComponentArray<Ennemy> enemies = world.getRegistry().get_components<Ennemy>();
    for (std::optional<Ennemy> enemy : enemies) {
        if (enemy && enemy.has_value()) {
            return (0);
        }
    }
    clockGenrationWorld.restartAndPause();
    world.resetFinishedLevel(true, server);
    return (0);
}
