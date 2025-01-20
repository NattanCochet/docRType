/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** DamageSystem
*/

#include "../../include/Systems.hpp"

int Systems::damageSystem(World &world, NetworkServer &server) {
    Registry &r = world.getRegistry();
    ComponentArray<Velocity> &velocity = r.get_components<Velocity>();
    ComponentArray<Position> &position = r.get_components<Position>();
    ComponentArray<Projectile> &projectile = r.get_components<Projectile>();

    std::size_t index = 0;
    std::size_t distanceScale = 300;

    for (auto &velEntry : velocity) {
        if (velEntry && velEntry.has_value() &&
            index < position.size() &&
            position[index] &&
            index < projectile.size() &&
            projectile[index]) {
            auto posPtr = position[index];
            auto projPtr = projectile[index];

            float distance = std::abs(posPtr->getPosition().x - posPtr->getDefaultPosition().x);
            float maxDistance = distanceScale * projPtr->getStack();

            if (distance > maxDistance) {
                projPtr->setStack(projPtr->getStack() + 1);
                float newDamage = projPtr->getDamage() * projPtr->getDmgFalloff();
                projPtr->setDamage(std::max(newDamage, 1.0f));
            }
        }
        index++;
    }
    return 0;
}
