/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** HitBoxSystem
*/

#include "../../include/Systems.hpp"

int Systems::hitboxSystem(World &world, NetworkServer &server)
{
    Registry &r = world.getRegistry();

    ComponentArray<Hitbox::Hitbox> &hitboxs = r.get_components<Hitbox::Hitbox>();
    ComponentArray<Position> &positions = r.get_components<Position>();

    static GJKAlgorithm algoCollision = GJKAlgorithm();

    const std::size_t hitboxCount = hitboxs.size();
    for (std::size_t index = 0; index < hitboxCount; index++) {
        std::optional<Hitbox::Hitbox> &hitboxOpt = hitboxs[index];
        if (!hitboxOpt.has_value() || index >= positions.size() || !positions[index].has_value()) {
            continue;
        }
        Hitbox::Hitbox &hitbox = *hitboxOpt;
        const sf::Vector2f &pos = positions[index]->getPosition();
        sf::Vector2f &mainPositionHitbox = hitbox.getPosition();
        const float dx = pos.x - mainPositionHitbox.x;
        const float dy = pos.y - mainPositionHitbox.y;
        const std::size_t &nbrHitboxs = hitbox.getNbrHitboxs();
        for (size_t i = 0; i < nbrHitboxs; i++) {
            Hitbox::RectHitbox &positionsHitbox = hitbox.getDataOfHitbox(i);
            positionsHitbox.XHitbox += dx;
            positionsHitbox.YHitbox += dy;
        }
        mainPositionHitbox = pos;
    }

    for (std::size_t index = 0; index < hitboxCount; index++) {
        std::optional<Hitbox::Hitbox> &hitboxOpt = hitboxs[index];
        if (!hitboxOpt.has_value() || index >= positions.size() || !positions[index].has_value()) {
            continue;
        }
        Hitbox::Hitbox &hitbox = *hitboxOpt;
        hitbox.resetCollisions();
        const std::size_t &nbrHitboxs = hitbox.getNbrHitboxs();
        for (size_t i = 0; i < nbrHitboxs; i++) {
            std::vector<std::pair<std::size_t, std::array<bool, 8>>> resultCollision =
                calculateCollision(hitboxs, index, i, algoCollision);
            for (std::pair<std::size_t, std::array<bool, 8>> result : resultCollision) {
                hitbox.addCollisionWithIDAndHitbox(i, result.first, result.second);
            }
        }
    }
    return (0);
}

std::vector<std::pair<std::size_t, std::array<bool, 8>>> Systems::calculateCollision(
    ComponentArray<Hitbox::Hitbox> &hitboxs, const std::size_t &indexToAnalyse, const std::size_t &indexHitbox,
    GJKAlgorithm &algoCollision)
{
    std::vector<std::pair<std::size_t, std::array<bool, 8>>> results;
    std::optional<std::array<bool, 8>> eightAnglesCollisions;
    std::size_t index = 0;
    Hitbox::Hitbox &shapeA = hitboxs[indexToAnalyse].value();

    for (std::optional<Hitbox::Hitbox> &hitbox : hitboxs) {
        if (index == indexToAnalyse || !hitbox.has_value()) {
            index += 1;
            continue;
        }
        Hitbox::Hitbox &shapeB = hitbox.value();
        if ((shapeA.getTeam() == shapeB.getTeam()) || (shapeA.getEntityID() == shapeB.getEntityID())) {
            index += 1;
            continue;
        }
        const std::size_t &nbrHitboxs = hitbox->getNbrHitboxs();
        for (std::size_t i = 0; i < nbrHitboxs; i++) {
            eightAnglesCollisions =
                algoCollision.gjkCollision(shapeA.getDataOfHitbox(indexHitbox), shapeB.getDataOfHitbox(i));
            if (!eightAnglesCollisions.has_value()) {
                continue;
            }
            results.emplace_back(index, eightAnglesCollisions.value());
        }
        index += 1;
    }

    return (results);
}
