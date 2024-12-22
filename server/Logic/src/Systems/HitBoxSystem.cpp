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

    GJKAlgorithm algoCollision = GJKAlgorithm();

    std::size_t index = 0;

    for (std::optional<Hitbox> hitbox : hitboxs) {
        if (hitbox && hitbox.has_value()) {
            if (positions[index] && positions[index].has_value()) {
                sf::Vector2f pos = positions[index]->getPosition();
                if (hitbox->getType() == Hitbox::CIRCULAR) {
                    hitbox->setPosition(pos.x, pos.y);
                } else {
                    hitbox->setPosition(pos.x - hitbox->getSize()[0], pos.y - hitbox->getSize()[1]);
                }
                std::vector<std::pair<std::size_t, std::array<bool, 8>>> resultCollision = calculateCollision(hitboxs, index, algoCollision);
                for (std::pair<std::size_t, std::array<bool, 8>> result : resultCollision) {
                    hitbox->addCollisionWithID(result.first, result.second);
                }
            }
        }
        index += 1;
    }
    return (0);
}

std::vector<std::pair<std::size_t, std::array<bool, 8>>> Systems::calculateCollision(ComponentArray<Hitbox> &hitboxs, std::size_t &indexToAnalyse, GJKAlgorithm &algoCollision)
{
    std::vector<std::pair<std::size_t, std::array<bool, 8>>> results;
    std::array<bool, 8> eightAnglesCollisions;
    std::size_t index = 0;

    for (std::optional<Hitbox> hitbox : hitboxs) {
        if (index == indexToAnalyse) {
            index += 1;
            continue;
        }
        Hitbox shapeA = hitboxs[indexToAnalyse].value();
        Hitbox shapeB = hitbox.value();
        eightAnglesCollisions = algoCollision.gjkCollision(shapeA, shapeB);
        if (eightAnglesCollisions.empty()) {
            index += 1;
            continue;
        }
        results.push_back(std::make_pair(index, eightAnglesCollisions));
        index += 1;
    }

    return (results);
}
