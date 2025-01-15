/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris [WSL: Ubuntu-22.04]
** File description:
** KamikazeShooter
*/

#include "../../../include/Components/Bots/KamikazeShooter.hpp"

KamikazeShooter::KamikazeShooter(float delay, float vSpeed, int damage)
{
    _delay = delay;
    _vSpeed = vSpeed;
    _damage = damage;
}

KamikazeShooter::~KamikazeShooter()
{
}

void KamikazeShooter::setVSpeed(float newVSpeed)
{
    _vSpeed = newVSpeed;
}

float KamikazeShooter::getVSpeed()
{
    return _vSpeed;
}

void KamikazeShooter::moveBot(World &world, std::size_t myIndexEntity)
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

void KamikazeShooter::shootProjectile(World &world, std::size_t myIndexEntity)
{
    std::optional<Velocity> &speed = world.getRegistry().get_components<Velocity>()[myIndexEntity];
    std::optional<Hitbox> &hitbox = world.getRegistry().get_components<Hitbox>()[myIndexEntity];
    std::optional<Position> &pos = world.getRegistry().get_components<Position>()[myIndexEntity];

    CreateEntity &create = world.getClassCreateEntity();

    if (!speed || !speed.has_value()) {
        return;
    }
    _vSpeed = 0;
    speed->setSpeed(-40, 0);
    create.createKamikaze(pos->getPosition(), world.getRegistry(), _damage, myIndexEntity, false);
}