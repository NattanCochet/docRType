/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** PositionSystem
*/

#include "../../include/Systems.hpp"

int Systems::positionSystem(World &world, NetworkServer &server)
{
    Registry &r = world.getRegistry();
    ComponentArray<Position> &positions = r.get_components<Position>();
    ComponentArray<Hitbox::Hitbox> &hitboxs = r.get_components<Hitbox::Hitbox>();
    const auto [windowWidth, windowHeight] = world.getSizeWindow();
    std::size_t sizeArrayPositions = positions.size();

    const auto isCircleInWindow = [windowWidth, windowHeight](const sf::Vector2f &pos, const sf::Vector2i &size) {
        const int radius = size.x;
        return (pos.x + radius >= 0 && pos.x - radius <= windowWidth) &&
               (pos.y + radius >= 0 && pos.y - radius <= windowHeight);
    };

    for (std::size_t index = 0; index < sizeArrayPositions; index++) {
        if (index >= positions.size() || !positions[index].has_value() ||
            index >= hitboxs.size() || !hitboxs[index].has_value()) {
            continue;
        }

        Position &position = positions[index].value();
        Hitbox::Hitbox &hitbox = hitboxs[index].value();

        const sf::Vector2f &pos = position.getPosition();
        const sf::Vector2i sizeHitbox = hitbox.getSizeHitbox(0);
        bool isInWindow = false;

        switch (hitbox.getType(0)) {
            case Hitbox::TYPE::RECTANGLE:
                isInWindow = isRectangleInWindow(windowWidth, windowHeight, pos, sizeHitbox, hitbox.getRotation(0));
                break;
            case Hitbox::TYPE::CIRCULAR:
                isInWindow = isCircleInWindow(pos, sizeHitbox);
                break;
            default:
                isInWindow = false;
                break;
        }
        if (!position.getIsAppearOnTheWindow() && isInWindow) {
            position.setIsAppearOnTheWindow(true);
        } else if (position.getIsAppearOnTheWindow() && !isInWindow) {
            world.sendToAllClientEntityDead(server, index, false);
            r.kill_entity(r.entity_from_index(index));
        }
    }
    return (0);
}

bool Systems::isRectangleInWindow(const std::size_t &windowWidth, const std::size_t &windowHeight, const sf::Vector2f &pos, const sf::Vector2i &size, const float &rotation)
{
    float rad = rotation * M_PI / 180.0f;
    float cos_r = std::cos(rad);
    float sin_r = std::sin(rad);

    std::array<sf::Vector2f, 4> corners = {
        sf::Vector2f(0, 0),
        sf::Vector2f(size.x, 0),
        sf::Vector2f(size.x, size.y),
        sf::Vector2f(0, size.y)
    };

    for (auto& corner : corners) {
        float x_rot = corner.x * cos_r - corner.y * sin_r;
        float y_rot = corner.x * sin_r + corner.y * cos_r;

        corner.x = x_rot + pos.x;
        corner.y = y_rot + pos.y;
    }

    for (const auto& corner : corners) {
        if (corner.x >= 0 && corner.x <= windowWidth &&
            corner.y >= 0 && corner.y <= windowHeight) {
            return (true);
        }
    }

    return (false);
}
