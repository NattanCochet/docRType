/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Star
*/

#include "../../../include/Components/Bonus/Star.hpp"

Star::Star(const float timeForInvincibility) :
    ABonus(), _time(timeForInvincibility), _clockForStar(), _isAlreadyRestart(false)
{
    _clockForStar.start();
}

Star::~Star()
{
}

bool Star::activate(World &world, std::size_t myIndexEntity)
{
    std::optional<Hitbox::Hitbox> &hitbox = world.getRegistry().get_components<Hitbox::Hitbox>()[myIndexEntity];

    if (!hitbox.has_value()) {
        return (true);
    }

    if (!this->_isAlreadyRestart) {
        this->_clockForStar.restart();
        for (Hitbox::RectHitbox &eachHitbox : hitbox->getAllHitboxs()) {
            eachHitbox.isActivate = false;
        }
        this->_isAlreadyRestart = true;
        return (false);
    }

    if (this->_clockForStar.getElapsedTime().asSeconds() <= this->_time) {
        return (false);
    }

    for (Hitbox::RectHitbox &eachHitbox : hitbox->getAllHitboxs()) {
        eachHitbox.isActivate = true;
    }
    return (true);
}
