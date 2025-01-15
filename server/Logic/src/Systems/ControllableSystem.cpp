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
    CreateEntity &ce = world.getClassCreateEntity();
    const std::pair<std::size_t, std::size_t> &sizeWindow = world.getSizeWindow();
    ComponentArray<Position> &position = r.get_components<Position>();
    ComponentArray<Controllable> &controllables = r.get_components<Controllable>();
    ComponentArray<Clock> &clocks = r.get_components<Clock>();
    ComponentArray<Hitbox> &hitboxs = r.get_components<Hitbox>();
    ComponentArray<Force> &forces = r.get_components<Force>();
    ComponentArray<Area> &areas = r.get_components<Area>();
    ComponentArray<Drawable::Drawable> &drawables = r.get_components<Drawable::Drawable>();

    std::size_t index = 0;

    for (std::optional<Controllable> &controllable : controllables) {
        if (!controllable.has_value() || index >= position.size() || !position[index].has_value() ||
            index >= clocks.size() || !clocks[index].has_value())
        {
            index += 1;
            continue;
        }
        VirtualKeyBoard &keyBoardControllable = controllable->getVirtualKeyboard();
        if (index < hitboxs.size() && hitboxs[index].has_value()) {
            movePlayerFromControllable(
                position[index]->getPosition(), hitboxs[index].value(),
                keyBoardControllable,
                clocks[index].value(), sizeWindow
            );
            position[index]->setPosition(position[index]->getPosition());
        }
        int indexForce = isForceEquipped(forces, index);
        if (indexForce != -1) {
            shootHandling(
                ce, r, keyBoardControllable,
                position[index].value(), clocks[index].value(), index,
                forces[indexForce].value()
            );
        } else {
            shootHandling(
                ce, r, keyBoardControllable,
                position[index].value(), clocks[index].value(), index
            );
        }
        if (index < areas.size() && areas[index].has_value()) {
            forceHandling(
                keyBoardControllable, clocks[index].value(), areas[index].value(),
                forces, position, index, drawables
            );
        }
        index += 1;
    }
    return (0);
}

void Systems::shootHandling(
    CreateEntity &ce, Registry &r, VirtualKeyBoard &keyboard, Position &currentPosition,
    Clock &clocks, const std::size_t &index, Force &forces
)
{
    static constexpr float SPAM_PROTECTION_DELAY = 0.1f;
    static constexpr float CHARGE_THRESHOLD = 0.3f;
    static constexpr float MAX_CHARGE_TIME = 1.1f;
    static constexpr float BASE_DAMAGE = 80.0f;

    sf::Clock &keyPressing = clocks.getClock("keyPressingShoot");
    sf::Clock &spamProtection = clocks.getClock("spamProtectionShoot");

    if (spamProtection.getElapsedTime().asSeconds() < SPAM_PROTECTION_DELAY) {
        return;
    }

    if (keyboard.isKeyIsPressed(VirtualKeyBoard::CONTROL::SHOOT)) {
        if (!keyboard.isChargingShoot()) {
            keyboard.setIsChargingShoot(true);
            keyPressing.restart();
        }
        return;
    }

    if (!keyboard.isChargingShoot()) {
        forces.stopShoot();
        return;
    }

    forces.haveToShoot();
    keyboard.setIsChargingShoot(false);
    const float chargeTime = keyPressing.getElapsedTime().asSeconds();

    if (chargeTime >= CHARGE_THRESHOLD) {
        const float clampedTime = std::min(chargeTime, MAX_CHARGE_TIME);
        const float damage = BASE_DAMAGE * (clampedTime / MAX_CHARGE_TIME);
        ce.createBeam(currentPosition.getPosition(), r, damage, index, true, true);
    } else {
        ce.createLaser(currentPosition.getPosition(), r, index, true, true);
    }

    spamProtection.restart();
}

void Systems::shootHandling(
    CreateEntity &ce, Registry &r, VirtualKeyBoard &keyboard, Position &currentPosition,
    Clock &clocks, const std::size_t &index
)
{
    static constexpr float SPAM_PROTECTION_DELAY = 0.1f;
    static constexpr float CHARGE_THRESHOLD = 0.3f;
    static constexpr float MAX_CHARGE_TIME = 1.1f;
    static constexpr float BASE_DAMAGE = 80.0f;

    sf::Clock &keyPressing = clocks.getClock("keyPressingShoot");
    sf::Clock &spamProtection = clocks.getClock("spamProtectionShoot");

    if (spamProtection.getElapsedTime().asSeconds() < SPAM_PROTECTION_DELAY) {
        return;
    }

    if (keyboard.isKeyIsPressed(VirtualKeyBoard::CONTROL::SHOOT)) {
        if (!keyboard.isChargingShoot()) {
            keyboard.setIsChargingShoot(true);
            keyPressing.restart();
        }
        return;
    }

    if (!keyboard.isChargingShoot()) {
        return;
    }

    keyboard.setIsChargingShoot(false);
    const float chargeTime = keyPressing.getElapsedTime().asSeconds();

    if (chargeTime >= CHARGE_THRESHOLD) {
        const float clampedTime = std::min(chargeTime, MAX_CHARGE_TIME);
        const float damage = BASE_DAMAGE * (clampedTime / MAX_CHARGE_TIME);
        ce.createBeam(currentPosition.getPosition(), r, damage, index, true, true);
    } else {
        ce.createLaser(currentPosition.getPosition(), r, index, true, true);
    }

    spamProtection.restart();
}

void Systems::movePlayerFromControllable(
    sf::Vector2f &pos, const Hitbox &hitbox, VirtualKeyBoard &keyboard, Clock &clock,
    const std::pair<std::size_t, std::size_t> &sizeWindow
)
{
    sf::Clock &movePlayer = clock.getClock("movePlayer");
    if (movePlayer.getElapsedTime().asMilliseconds() <= 16) {
        return;
    }

    static const float speedValue = 15; // a changer en fonction de la vitesse

    float newPosX = 0.0f;
    float newPosY = 0.0f;

    if (keyboard.isKeyIsPressed(VirtualKeyBoard::CONTROL::DOWN)) {
        if (!hitbox.isCollisionInDirection(Hitbox::DIRECTION::DOWN) &&
            pos.y + hitbox.getSize()[1] <= sizeWindow.second) {
            newPosY += speedValue;
        }
    }

    if (keyboard.isKeyIsPressed(VirtualKeyBoard::CONTROL::RIGHT)) {
        if (!hitbox.isCollisionInDirection(Hitbox::DIRECTION::RIGHT) &&
            pos.x + hitbox.getSize()[0] <= sizeWindow.first) {
            newPosX += speedValue;
        }
    }

    if (keyboard.isKeyIsPressed(VirtualKeyBoard::CONTROL::LEFT)) {
        if (!hitbox.isCollisionInDirection(Hitbox::DIRECTION::LEFT) &&
            pos.x >= 0) {
            newPosX -= speedValue;
        }
    }

    if (keyboard.isKeyIsPressed(VirtualKeyBoard::CONTROL::UP)) {
        if (!hitbox.isCollisionInDirection(Hitbox::DIRECTION::UP) &&
            pos.y >= 0) {
            newPosY -= speedValue;
        }
    }

    if (newPosX != 0.0f && newPosY != 0.0f) {
        float scale = speedValue / (std::sqrt(newPosX * newPosX + newPosY * newPosY));
        newPosX *= scale;
        newPosY *= scale;
    }
    pos.x += newPosX;
    pos.y += newPosY;
    movePlayer.restart();
}

void Systems::forceHandling(
    VirtualKeyBoard &keyboard, Clock &clocks, Area &areaControllable, ComponentArray<Force> &forces,
    ComponentArray<Position> &position, const std::size_t &idBelong, ComponentArray<Drawable::Drawable> &drawable
)
{
    static constexpr float SPAM_PROTECTION_DELAY = 0.1f;
    static constexpr float CHARGE_THRESHOLD = 0.3f;
    static constexpr float MAX_CHARGE_TIME = 1.1f;
    static constexpr float BASE_DAMAGE = 80.0f;

    sf::Clock &keyPressing = clocks.getClock("keyPressingForce");
    sf::Clock &spamProtection = clocks.getClock("spamProtectionForce");

    if (spamProtection.getElapsedTime().asSeconds() < SPAM_PROTECTION_DELAY) {
        return;
    }

    if (keyboard.isKeyIsPressed(VirtualKeyBoard::CONTROL::FORCE)) {
        if (!keyboard.isChargingForce()) {
            keyboard.setIsChargingForce(true);
            keyPressing.restart();
        }
        return;
    }

    if (!keyboard.isChargingForce()) {
        return;
    }

    keyboard.setIsChargingForce(false);
    const float chargeTime = keyPressing.getElapsedTime().asSeconds();

    if (chargeTime >= CHARGE_THRESHOLD) {
        const float clampedTime = std::min(chargeTime, MAX_CHARGE_TIME);
        const float damage = BASE_DAMAGE * (clampedTime / MAX_CHARGE_TIME);
        shootForwardForce(forces, damage);
    } else {
        equipedForce(areaControllable, forces, position, idBelong, drawable);
    }

    spamProtection.restart();
}

void Systems::shootForwardForce(ComponentArray<Force> &forces, const float &damage)
{
    std::size_t index = 0;

    for (std::optional<Force> &force : forces) {
        if (!force || !force.has_value()) {
            index += 1;
            continue;
        }
        if (force->isEquipped()) {
            force->stopShoot();
            force->shootForwardForce(damage);
            return;
        }
        index += 1;
    }
}

void Systems::equipedForce(
    const Area &areaControllable, ComponentArray<Force> &forces, ComponentArray<Position> &position,
    const std::size_t &idBelong, ComponentArray<Drawable::Drawable> &drawable
)
{
    std::size_t index = 0;

    for (std::optional<Force> &force : forces) {
        if (!force || !force.has_value()) {
            index += 1;
            continue;
        }
        if (!force->isEquipped() && force->getIdBelongForce() >= 0) {
            force->reattachedForce();
            return;
        }
        if (force->isEquipped()) {
            force->unEquipped();
            return;
        }
        if (areaControllable.isInAreaOfEntity(index)) {
            float sizeForce = 0.0;
            float sizeControllable = 0.0;
            if (index < drawable.size() && idBelong < drawable.size() && drawable[index].has_value() && drawable[idBelong].has_value()) {
                sizeForce = (drawable[index]->getCurrentRect()._rectWidth * drawable[index]->getScale().x) / 2;
                sizeControllable = (drawable[idBelong]->getCurrentRect()._rectWidth * drawable[idBelong]->getScale().x) / 2;
            }
            force->equipped(idBelong, isToTheRight(position, idBelong, index, sizeForce, sizeControllable));
            return;
        }
        index += 1;
    }
}

bool Systems::isToTheRight(
    ComponentArray<Position> &position, const std::size_t &idBelong, const std::size_t &index,
    const float &sizeForce, const float &sizeControllable
)
{
    sf::Vector2f &posControllable = position[idBelong].value().getPosition();
    sf::Vector2f &posForce = position[index].value().getPosition();

    return (posForce.x - sizeForce >= posControllable.x - sizeControllable);
}

int Systems::isForceEquipped(ComponentArray<Force> &forces, const std::size_t &index)
{
    int indexEntity = 0;

    for (std::optional<Force> &force : forces) {
        if (!force || !force.has_value()) {
            indexEntity++;
            continue;
        }
        if (force->isEquipped() && force->getIdBelongForce() == index) {
            return (indexEntity);
        }
        indexEntity++;
    }
    return (-1);
}
