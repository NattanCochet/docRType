/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** SpawnSystem
*/

#include "../../include/Systems.hpp"

int Systems::spawnSystem(World &world, NetworkServer &server)
{
    if (world.getIsLevelFinishedToSpawn()) {
        return (0);
    }
    MyClock &clockGenerationWorld = world.getClockGenerationWorld();
    if (world.isBeginingOfSpwan() || clockGenerationWorld.getElapsedTime().asSeconds() >= world.getSpawnTimeThreshold()) {
        world.spawnEntitiesInWorld();
        clockGenerationWorld.restart();
    }
    return (0);
}
