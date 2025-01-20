/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** UpgradeForce
*/

#include "../../../include/Components/Bonus/UpgradeForce.hpp"

UpgradeForce::UpgradeForce() : ABonus()
{
}

UpgradeForce::~UpgradeForce()
{
}

bool UpgradeForce::activate(World &world, std::size_t myIndexEntity)
{
    Registry &r = world.getRegistry();

    ComponentArray<Force> &forces = r.get_components<Force>();

    for (std::optional<Force> &force : forces) {
        if (!force.has_value()) {
            continue;
        }
        if (force->getIdBelongForce() == myIndexEntity) {
            force->upgrade();
            return (true);
        }
    }
    return (true);
}
