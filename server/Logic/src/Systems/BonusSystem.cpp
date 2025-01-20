/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** BonusSystem
*/

#include "../../include/Systems.hpp"

int Systems::bonusSystem(World &world, NetworkServer &server)
{
    Registry &r = world.getRegistry();

    ComponentArray<Bonus> &bonuses = r.get_components<Bonus>();
    ComponentArray<Area> &areas = r.get_components<Area>();

    std::size_t index = 0;

    for (std::optional<Bonus> &bonus : bonuses) {
        if (!bonus.has_value()) {
            index += 1;
            continue;
        }
        std::shared_ptr<ABonus> &bon = bonus->getBonus();
        if (bon->getIsEquipped()) {
            if (bon->activate(world, bon->getIdBelong())) {
                world.sendToAllClientEntityDead(server, index, false);
                r.kill_entity(r.entity_from_index(index));
            } else {
                r.remove_component<Area>(r.entity_from_index(index));
                r.remove_component<Drawable::Drawable>(r.entity_from_index(index));
            }
            index += 1;
            continue;
        }
        if (index < areas.size() && areas[index].has_value()) {
            checkIfEquippedBonus(bon, areas[index].value(), r);
        } else {
            world.sendToAllClientEntityDead(server, index, false);
            r.kill_entity(r.entity_from_index(index));
        }
    }
    return (0);
}

void Systems::checkIfEquippedBonus(std::shared_ptr<ABonus> &bon, Area &areaBonus, Registry &r)
{
    ComponentArray<Controllable> &controllables = r.get_components<Controllable>();

    std::size_t index = 0;

    for (std::optional<Controllable> controllable : controllables) {
        if (!controllable.has_value() || !controllable->getIsPlayer()) {
            index += 1;
            continue;
        }
        if (areaBonus.isInAreaOfEntity(index)) {
            bon->isEquipped(index);
            return;
        }
        index += 1;
    }
}
