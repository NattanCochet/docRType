/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** HitBoxSystem
*/

#include "../../include/Systems.hpp"

int Systems::hitboxSystem(World &world)
{
    Registry &r = world.getRegistry();

    ComponentArray<Hitbox> &hitboxs = r.get_components<Hitbox>();
    ComponentArray<Position> &positions = r.get_components<Position>();

    static GJKAlgorithm algoCollision = GJKAlgorithm();

    std::size_t index = 0;

    for (std::optional<Hitbox> &hitbox : hitboxs) {
        if (!hitbox || !hitbox.has_value() || index >= positions.size() || !positions[index].has_value()) {
            index += 1;
            continue;
        }
        const sf::Vector2f &pos = positions[index]->getPosition();
        hitbox->resetCollisions();
        hitbox->setPosition(pos.x, pos.y);
        std::vector<std::pair<std::size_t, std::array<bool, 8>>> resultCollision = calculateCollision(hitboxs, index, algoCollision);
        for (std::pair<std::size_t, std::array<bool, 8>> result : resultCollision) {
            hitbox->addCollisionWithID(result.first, result.second);
        }
        index += 1;
    }
    return (0);
}

std::vector<std::pair<std::size_t, std::array<bool, 8>>> Systems::calculateCollision(ComponentArray<Hitbox> &hitboxs, std::size_t &indexToAnalyse, GJKAlgorithm &algoCollision)
{
    std::vector<std::pair<std::size_t, std::array<bool, 8>>> results;
    std::optional<std::array<bool, 8>> eightAnglesCollisions;
    std::size_t index = 0;

    for (std::optional<Hitbox> &hitbox : hitboxs) {
        if (index == indexToAnalyse || !hitbox.has_value()) {
            index += 1;
            continue;
        }
        Hitbox &shapeA = hitboxs[indexToAnalyse].value();
        Hitbox &shapeB = hitbox.value();
        if ((shapeA.isInPlayerTeams() && shapeB.isInPlayerTeams()) || (shapeA.getEntityID() == shapeB.getEntityID())) {
            index += 1;
            continue;
        }
        eightAnglesCollisions = algoCollision.gjkCollision(shapeA, shapeB);
        if (!eightAnglesCollisions.has_value()) {
            index += 1;
            continue;
        }
        results.push_back(std::make_pair(index, eightAnglesCollisions.value()));
        index += 1;
    }

    return (results);
}
