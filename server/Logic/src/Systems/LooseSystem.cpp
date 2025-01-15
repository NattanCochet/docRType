/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** LooseSystem
*/

#include "../../include/Systems.hpp"

int Systems::looseSystem(World &world)
{
    Registry &r = world.getRegistry();

    const ComponentArray<Controllable> &contrallables = r.get_components<Controllable>();

    for (std::optional<Controllable> c : contrallables) {
        if (c && c.has_value() && c->getIsPlayer()) {
            return (0);
        }
    }
    world.resetFinishedLevel(false);
    return (0);
}
