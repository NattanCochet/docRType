/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ControllableSystem
*/

#include "../../include/Systems.hpp"

int Systems::controllableSystem(World &world)
{
    Registry &r = world.getRegistry();
    ComponentArray<Position> &position = r.get_components<Position>();
    ComponentArray<Controllable> &controllables = r.get_components<Controllable>();
    ComponentArray<Clock> &clocks = r.get_components<Clock>();
    ComponentArray<Hitbox> &hitboxs = r.get_components<Hitbox>();

    std::size_t index = 0;

    for (std::optional<Controllable> controllable : controllables) {
        if (controllable && controllable.has_value()) {
            if (position[index] && position[index].has_value()) {
                if (clocks[index] && clocks[index].has_value()) {
                    if (hitboxs[index] && hitboxs[index].has_value()) {
                        movePlayerFromControllable(
                            position[index]->getPosition(), hitboxs[index].value(),
                            world.getVirtualKeyBoardFromClientID(controllable->getClientID()),
                            clocks[index].value()
                        );
                        position[index]->setPosition(position[index]->getPosition());
                    }
                    shootHandling(r, world.getVirtualKeyBoardFromClientID(controllable->getClientID()), position[index].value(), clocks[index].value());
                }
            }
        }
        index += 1;
    }
    return (0);
}

void Systems::shootHandling(Registry &r, VirtualKeyBoard &keyboard, Position &currentPosition, Clock &clocks)
{
    sf::Clock &keyPressing = clocks.getClock("keyPressing");
    sf::Clock &spamProtection = clocks.getClock("spamProtection");

    if (keyboard.isKeyIsPressed(VirtualKeyBoard::CONTROL::SHOOT)) {
        if (!keyboard.isCharging()) {
            keyboard.setIsCharging(true);
            keyPressing.restart();

            if (spamProtection.getElapsedTime().asSeconds() >= 0.1f) {
                auto laser = r.spawn_entity();
                r.add_component(laser, Projectile(20.0f, 0.0f, false, false, 0.0f, 0.4f));
                r.add_component(laser, Velocity(sf::Vector2i(5.0f, 0), 0.0, 0.0));
                r.add_component(laser, Position(currentPosition.getPosition().x, currentPosition.getPosition().y));
                spamProtection.restart();
            }
        }
    } else if (keyboard.isCharging()) {
        keyboard.setIsCharging(false);
        auto laser = r.spawn_entity();

        if (keyPressing.getElapsedTime().asSeconds() >= 0.4f) {
            r.add_component(laser, Projectile(80.0f, 0.0f, false, true, 0.2f, 0.2f));
            r.add_component(laser, Velocity(sf::Vector2i(2.0f, 0), 0.0, 0.0));
        } else {
            r.add_component(laser, Projectile(20.0f, 0.0f, false, false, 0.0f, 0.4f));
            r.add_component(laser, Velocity(sf::Vector2i(5.0f, 0), 0.0, 0.0));
        }

        r.add_component(laser, Position(currentPosition.getPosition().x, currentPosition.getPosition().y));
    }
}

void Systems::movePlayerFromControllable(sf::Vector2f &pos, const Hitbox &hitbox, VirtualKeyBoard &keyboard, Clock &clock)
{
    sf::Clock &movePlayer = clock.getClock("movePlayer");
    if (movePlayer.getElapsedTime().asMilliseconds() <= 16) {
        return;
    }

    static float speedValue = 0.5; // a changer en fonction de la vitesse

    float newPosX = 0.0f;
    float newPosY = 0.0f;

    if (keyboard.isKeyIsPressed(VirtualKeyBoard::CONTROL::DOWN)) {
        if (!hitbox.isCollisionInDirection(Hitbox::DIRECTION::DOWN)) {
            newPosY += speedValue;
        }
    }

    if (keyboard.isKeyIsPressed(VirtualKeyBoard::CONTROL::RIGHT)) {
        if (!hitbox.isCollisionInDirection(Hitbox::DIRECTION::RIGHT)) {
            newPosX += speedValue;
        }
    }

    if (keyboard.isKeyIsPressed(VirtualKeyBoard::CONTROL::LEFT)) {
        if (!hitbox.isCollisionInDirection(Hitbox::DIRECTION::LEFT)) {
            newPosX -= speedValue;
        }
    }

    if (keyboard.isKeyIsPressed(VirtualKeyBoard::CONTROL::UP)) {
        if (!hitbox.isCollisionInDirection(Hitbox::DIRECTION::UP)) {
            newPosY -= speedValue;
        }
    }

    if (newPosX != 0.0f && newPosY != 0.0f) {
        float length = std::sqrt(newPosX * newPosX + newPosY * newPosY);
        newPosX /= length;
        newPosY /= length;
    }
    pos.x += newPosX;
    pos.y += newPosY;
    movePlayer.restart();
}
