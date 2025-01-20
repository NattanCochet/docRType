/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ProjectileSystem
*/

#include "../../include/Systems.hpp"

#include <boost/atomic.hpp>
#include <boost/random.hpp>

int Systems::ProjectileSystem(World &world, NetworkServer &server)
{
    Registry &r = world.getRegistry();

    ComponentArray<Hitbox::Hitbox> &hitboxs = r.get_components<Hitbox::Hitbox>();
    ComponentArray<Projectile> &projectiles = r.get_components<Projectile>();
    ComponentArray<Vitality> &vitalities = r.get_components<Vitality>();

    std::size_t index = 0;

    for (std::optional<Projectile> &projectile : projectiles) {
        if (!projectile || !projectile.has_value() || index >= hitboxs.size() || !hitboxs[index].has_value()) {
            index += 1;
            continue;
        }
        std::vector<std::size_t> collisionIDs = hitboxs[index]->getAllCollisionIDs();
        for (std::size_t collisionID : collisionIDs) {
            if (!world.isEntityPresent(collisionID)) {
                continue;
            }

            if (collisionID >= vitalities.size() || !vitalities[collisionID].has_value()) {
                world.sendToAllClientEntityDead(server, index, false);
                r.kill_entity(r.entity_from_index(index));
                continue;
            }
            if (!projectile->isEntityIDAlreadyTouch(collisionID)) {
                if (isHitboxHittenIsActivated(hitboxs, index, collisionID)) {
                    vitalities[collisionID]->damageEntity(std::round(projectile->getDamage()));
                }
                projectile->addEntityIDAlreadyTouch(collisionID);
                attributeScore(world, vitalities[collisionID], projectile);
            }

            if (!projectile->getCanHoldCharge()) {
                world.sendToAllClientEntityDead(server, index, false);
                r.kill_entity(r.entity_from_index(index));
            }
        }
        index += 1;
    }
    return (0);
}

void Systems::attributeScore(World &world, std::optional<Vitality> &vitality, std::optional<Projectile> &projectile)
{
    if (!vitality->isDead()) {
        return;
    }
    Registry &r = world.getRegistry();

    ComponentArray<Controllable> controllables = r.get_components<Controllable>();
    std::size_t shooterID = projectile->getEntityIDBelong();

    if (shooterID >= controllables.size() || !controllables[shooterID].has_value()) {
        return;
    }

    Controllable &controlableShooter = controllables[shooterID].value();

    std::size_t entityID = vitality->getEntityID();
    SpawnRule::Generator &srg = world.getClassSpawnRuleGenerator();
    try {
        SpawnRule::EntityType &entity = srg.getEntity(entityID);
        world.getClientsID()[controlableShooter.getClientID()].addScore(entity.scoreByDeath, world.getCurrentLevel());
    }
    catch (ErrorKeyNotFound &e) {
        std::cerr << e.what() << "\n";
    }
    return;
}

bool Systems::isHitboxHittenIsActivated(
    ComponentArray<Hitbox::Hitbox> &hitboxs, std::size_t indexCollision, std::size_t collisionWithEntityID)
{
    if (collisionWithEntityID >= hitboxs.size() || !hitboxs[collisionWithEntityID].has_value()) {
        return (true);
    }
    std::size_t index = 0;
    try {
        index = hitboxs[collisionWithEntityID]->getHitboxsIndexInCollisionsWithEntityID(indexCollision);
    }
    catch (ErrorKeyNotFound &e) {
        return (true);
    }
    const Hitbox::RectHitbox &rectHitbox = hitboxs[collisionWithEntityID]->getDataOfHitbox(index);
    return (rectHitbox.isActivate);
}
