/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** SpawnAfterDeadSystem
*/

#include "../../include/Systems.hpp"

int Systems::spawnAfterDeadSystem(World &world)
{
    Registry &r = world.getRegistry();
    ComponentArray<SpawnAfterDead> &sads = r.get_components<SpawnAfterDead>();
    ComponentArray<Position> &positions = r.get_components<Position>();

    std::size_t index = 0;

    for (std::optional<SpawnAfterDead> sad : sads) {
        if (!sad || !sad.has_value() || index >= positions.size() ||
            !positions[index] || !positions[index].has_value() || !sad->getIsDead()
        ) {
            index += 1;
            continue;
        }
        const sf::Vector2f &pos = positions[index]->getPosition();
        world.spawnEntityFromGeneratedWorld(sad->getIdBeforeDead(), pos.x, pos.y);
        r.kill_entity(r.entity_from_index(index));
    }
    return (0);
}
