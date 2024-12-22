/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ProjectileSystem
*/

#include "../../include/Systems.hpp"

int Systems::ProjectileSystem(World &world)
{
    Registry &r = world.getRegistry();

    ComponentArray<Hitbox> &hitboxs = r.get_components<Hitbox>();
    ComponentArray<Projectile> &projectiles = r.get_components<Projectile>();
    ComponentArray<Vitality> &vitalities = r.get_components<Vitality>();

    std::size_t index = 0;

    std::size_t indexEntityVitality = 0;

    for (std::optional<Projectile> projectile : projectiles) {
        if (hitboxs.size() > 0 && projectile && projectile.has_value() && hitboxs[index] && hitboxs[index].has_value()) {
            for (std::optional<Vitality> vitality : vitalities) {
                if (vitality && vitality.has_value()) {
                    if (hitboxs[index]->isCollisionWithID(indexEntityVitality)) {
                        vitality->damageEntity(std::round(projectile->getDamage()));
                    }
                }
                indexEntityVitality += 1;
            }
        }
        index += 1;
        indexEntityVitality = 0;
    }
    return (0);
}
