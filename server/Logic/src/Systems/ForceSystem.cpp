/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ForceSystem
*/

#include "../../include/Systems.hpp"

int Systems::forceSystem(World &world, NetworkServer &server)
{
    Registry &r = world.getRegistry();

    ComponentArray<Force> &forces = r.get_components<Force>();
    ComponentArray<Position> &positions = r.get_components<Position>();
    ComponentArray<Velocity> &velocities = r.get_components<Velocity>();
    ComponentArray<Hitbox::Hitbox> &hitboxs = r.get_components<Hitbox::Hitbox>();
    ComponentArray<Drawable::Drawable> &drawables = r.get_components<Drawable::Drawable>();

    std::size_t index = 0;

    for (std::optional<Force> &force : forces) {
        if (!force || !force.has_value() || index >= positions.size() || !positions[index].has_value() ||
            index >= drawables.size() || !drawables[index].has_value()) {
            index += 1;
            continue;
        }
        if (index < velocities.size() && velocities[index] && velocities[index].has_value()) {
            if (!force->isShootForward()) {
                int &xFinal = force->getFinalPosition();
                if (xFinal <= positions[index]->getPosition().x) {
                    xFinal = 0;
                    r.remove_component<Velocity>(r.entity_from_index(index));
                }
            } else if (touchTheBorderScreen(
                           positions[index]->getPosition().x, world.getSizeWindow(), drawables, index)) {
                force->stopShootingForward();
                r.remove_component<Velocity>(r.entity_from_index(index));
                r.remove_component<Projectile>(r.entity_from_index(index));
                r.remove_component<Hitbox::Hitbox>(r.entity_from_index(index));
            }
            index += 1;
            continue;
        }
        if (force->isShootForward()) {
            if (index < hitboxs.size() && hitboxs[index].has_value()) {
                float dir = force->getIsShootToTheRight() ? 12.0 : -12.0;
                r.add_component(r.entity_from_index(index), Velocity(dir, 0.0, 0.0, 0.01));
                r.add_component(
                    r.entity_from_index(index), Projectile(force->getInitialDamage(), false, true, 1.0, index));
            }
            index += 1;
            continue;
        }
        if (!force->isEquipped()) {
            if (index < hitboxs.size() && hitboxs[index] && hitboxs[index].has_value()) {
                r.remove_component<Hitbox::Hitbox>(r.entity_from_index(index));
            }
            index += 1;
            continue;
        }
        const std::size_t &indexBelong = static_cast<std::size_t>(force->getIdBelongForce());

        if (force->HaveIToCheckSkin()) {
            changeSkinForce(force.value(), drawables[index].value());
        }

        if (index < hitboxs.size() && (!hitboxs[index] || !hitboxs[index].has_value())) {
            const Drawable::FrameRect &rect = drawables[index]->getCurrentRect();
            const sf::Vector2f &scale = drawables[index]->getScale();
            r.add_component(r.entity_from_index(index),
                Hitbox::Hitbox(positions[index]->getPosition(),
                    {Hitbox::RectHitbox(Hitbox::TYPE::RECTANGLE, positions[index]->getPosition(),
                        rect._rectWidth * scale.x, rect._rectHeight * scale.y, 0.0f)},
                    indexBelong, Hitbox::TEAM::PLAYER));
        }

        if (indexBelong >= positions.size() || !positions[indexBelong].has_value()) {
            index += 1;
            continue;
        }

        moveForceNextToThePlayer(r, index, indexBelong);
        shootWithForce(world, index, indexBelong);
    }
    return (0);
}

void Systems::moveForceNextToThePlayer(Registry &r, const std::size_t &index, const std::size_t &indexBelong)
{
    std::optional<Force> &force = r.get_components<Force>()[index];
    std::optional<Drawable::Drawable> &drwForce = r.get_components<Drawable::Drawable>()[index];
    std::optional<Position> &posForce = r.get_components<Position>()[index];
    std::optional<Drawable::Drawable> &drwOwner = r.get_components<Drawable::Drawable>()[indexBelong];
    std::optional<Position> &posOwner = r.get_components<Position>()[indexBelong];

    if (!drwForce || !drwForce.has_value() || !posForce || !posForce.has_value() || !drwOwner ||
        !drwOwner.has_value() || !posOwner || !posOwner.has_value() || !force || !force.has_value()) {
        return;
    }
    sf::Vector2f &coordPos = posForce->getPosition();
    const sf::Vector2f &coordOwner = posOwner->getPosition();
    if (force->getIsShootToTheRight()) {
        coordPos.x = coordOwner.x + (drwOwner->getCurrentRect()._rectWidth * drwOwner->getScale().x);
    } else {
        coordPos.x = coordOwner.x - (drwForce->getCurrentRect()._rectWidth * drwForce->getScale().x);
    }
    coordPos.y = coordOwner.y + ((drwForce->getCurrentRect()._rectHeight * drwForce->getScale().y) / 2);
}

void Systems::shootWithForce(World &world, const std::size_t &index, const std::size_t &indexBelong)
{
    Registry &r = world.getRegistry();
    std::optional<Force> &force = r.get_components<Force>()[index];
    std::optional<Position> &posForce = r.get_components<Position>()[index];

    if (!force || !force.has_value() || !posForce || !posForce.has_value()) {
        return;
    }

    if (!force->getHaveIToShoot()) {
        return;
    }

    sf::Clock &clockShoot = force->getClockShoot();
    if (clockShoot.getElapsedTime().asSeconds() >= 0.2f) {
        world.getClassCreateEntity().createShootForce(
            posForce->getPosition(), r, indexBelong, force->getIsShootToTheRight(), force->getLevelForce());
        clockShoot.restart();
    }
}

bool Systems::touchTheBorderScreen(float posX, std::pair<std::size_t, std::size_t> sizeWindow,
    ComponentArray<Drawable::Drawable> &drawables, std::size_t index)
{
    if (index < drawables.size() && drawables[index].has_value()) {
        return (posX <= 0 || posX >= sizeWindow.first - (drawables[index]->getCurrentRect()._rectWidth *
                                                            drawables[index]->getScale().x));
    }
    return (false);
}

void Systems::changeSkinForce(Force &force, Drawable::Drawable &drawable)
{
    if (force.getIsShootToTheRight()) {
        switch (force.getLevelForce()) {
        case 0:
            {
                drawable.setType("Force1");
                drawable.setDefaultFrame({Drawable::FrameRect(0, 0, 24, 18), Drawable::FrameRect(24, 0, 24, 18),
                    Drawable::FrameRect(48, 0, 24, 18), Drawable::FrameRect(72, 0, 24, 18),
                    Drawable::FrameRect(96, 0, 24, 18), Drawable::FrameRect(110, 0, 24, 18)});
                break;
            }
        case 1:
            {
                drawable.setType("ForceR2");
                drawable.setDefaultFrame({Drawable::FrameRect(0, 0, 28, 24), Drawable::FrameRect(28, 0, 28, 24),
                    Drawable::FrameRect(56, 0, 28, 24), Drawable::FrameRect(84, 0, 28, 24),
                    Drawable::FrameRect(112, 0, 28, 24), Drawable::FrameRect(140, 0, 28, 24)});
                break;
            }
        case 2:
            {
                drawable.setType("ForceR3");
                drawable.setDefaultFrame({Drawable::FrameRect(0, 34, 32, 34), Drawable::FrameRect(32, 34, 32, 34),
                    Drawable::FrameRect(64, 34, 32, 34), Drawable::FrameRect(96, 34, 32, 34)});
                break;
            }

        default:
            break;
        }
    } else {
        switch (force.getLevelForce()) {
        case 0:
            {
                drawable.setType("Force1");
                drawable.setDefaultFrame({Drawable::FrameRect(0, 0, 24, 18), Drawable::FrameRect(24, 0, 24, 18),
                    Drawable::FrameRect(48, 0, 24, 18), Drawable::FrameRect(72, 0, 24, 18),
                    Drawable::FrameRect(96, 0, 24, 18), Drawable::FrameRect(110, 0, 24, 18)});
                break;
            }
        case 1:
            {
                drawable.setType("ForceL2");
                drawable.setDefaultFrame({Drawable::FrameRect(0, 24, 28, 24), Drawable::FrameRect(28, 24, 28, 24),
                    Drawable::FrameRect(56, 24, 28, 24), Drawable::FrameRect(84, 24, 28, 24),
                    Drawable::FrameRect(112, 24, 28, 24), Drawable::FrameRect(140, 24, 28, 24)});
                break;
            }
        case 2:
            {
                drawable.setType("ForceL3");
                drawable.setDefaultFrame({Drawable::FrameRect(0, 0, 32, 34), Drawable::FrameRect(32, 0, 32, 34),
                    Drawable::FrameRect(64, 0, 32, 34), Drawable::FrameRect(96, 0, 32, 34)});
                break;
            }

        default:
            break;
        }
    }
    force.checkSkinDone();
}
