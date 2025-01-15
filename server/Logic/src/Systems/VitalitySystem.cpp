/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** VitalitySystem
*/

#include "../../include/Systems.hpp"

int Systems::vitalitySystem(World &world)
{
    Registry &r = world.getRegistry();
    ComponentArray<Vitality> &vitalities = r.get_components<Vitality>();
    ComponentArray<SpawnAfterDead> &sad = r.get_components<SpawnAfterDead>();
    std::size_t index = 0;

    for (std::optional<Vitality> vitality : vitalities) {
        if (vitality && vitality.has_value()) {
            if (vitality->isDead()) {
                if (index < sad.size() && sad[index].has_value()) {
                    sad[index]->entityIsDead();
                } else {
                    r.kill_entity(r.entity_from_index(index));
                }
            }
        }
        index += 1;
    }
    return (0);
}
