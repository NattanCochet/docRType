/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** LinearShooter
*/

#include "../../../include/Components/Bots/LinearShooter.hpp"

LinearShooter::LinearShooter(float delay, bool honrizontal, int vSpeed)
{
    _delay = delay;
    _honrizontal = honrizontal;
    _vSpeed = vSpeed;
}

void LinearShooter::moveBot(World &world, std::size_t myIndexEntity)
{
    std::optional<Position> &pos = world.getRegistry().get_components<Position>()[myIndexEntity];
    std::optional<Drawable::Drawable> &draw = world.getRegistry().get_components<Drawable::Drawable>()[myIndexEntity];
    std::size_t heightWindow = world.getHeightWindow();

    if (!pos || !pos.has_value() || !draw || !draw.has_value()) {
        return;
    }
    sf::Vector2f &coordsAct = pos->getPosition();
    const int heightRect = draw->getCurrentRect()._rectHeight;
    if ((coordsAct.y >= heightWindow - heightRect || coordsAct.y <= 0)) {
        this->_vSpeed *= -1;
    }
    coordsAct.y += this->_vSpeed;
}

void LinearShooter::shootProjectile(World &world, std::size_t myIndexEntity)
{
    CreateEntity &c = world.getClassCreateEntity();
    std::optional<Position> &pos = world.getRegistry().get_components<Position>()[myIndexEntity];

    if (!pos || !pos.has_value() || !pos->getIsAppearOnTheWindow()) {
        return;
    }

    if (this->_honrizontal) {
        c.createBomb(pos->getPosition(), world.getRegistry(), myIndexEntity, false);
    } else {
        c.createLaser(pos->getPosition(), world.getRegistry(), myIndexEntity, false, false);
    }
}
