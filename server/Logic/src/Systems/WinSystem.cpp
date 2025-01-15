/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** WinSystem
*/

#include "../../include/Systems.hpp"

int Systems::winSystem(World &world)
{
    if (!world.getIsLevelFinishedToSpawn()) {
        return (0);
    }
    MyClock &clockGenrationWorld = world.getClockGenerationWorld();
    if (clockGenrationWorld.getElapsedTime().asSeconds() < world.getSpawnTimeThreshold()) {
        return (0);
    }
    clockGenrationWorld.restartAndPause();
    if (world.getBossIDAtTheEnd() == -1) {
        world.resetFinishedLevel(true);
        return (0);
    }
    // attendre que le boss soit mort pour reinitalise la partie
    return (0);
}
