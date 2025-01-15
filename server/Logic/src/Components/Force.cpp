/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Force
*/

#include "../../include/Components/Force.hpp"

Force::Force(int x)
    : _xFinal(x), _idBelong(-1), _levelForce(0), _haveToShoot(false),
      _toTheRight(true), _clockShoot(), _isShootForward(false), _initialeDamage(0.0), _isEquipped(false)
{
}

Force::~Force()
{
}

int &Force::getFinalPosition() noexcept
{
    return (this->_xFinal);
}

const bool &Force::isEquipped() const noexcept
{
    return (this->_isEquipped);
}

const std::size_t &Force::getLevelForce() const noexcept
{
    return (this->_levelForce);
}

const int &Force::getIdBelongForce() const noexcept
{
    return (this->_idBelong);
}

const bool &Force::getIsShootToTheRight() const noexcept
{
    return (this->_toTheRight);
}

void Force::equipped(const std::size_t &idBelongForce, const bool &isToTheRight)
{
    if (this->_isEquipped || this->_idBelong >= 0 || this->_xFinal > 0) {
        return;
    }
    this->_isEquipped = true;
    this->_idBelong = idBelongForce;
    this->_toTheRight = isToTheRight;
}

void Force::unEquipped() noexcept
{
    this->_idBelong = -1;
    this->_isEquipped = false;
}

void Force::upgrade() noexcept
{
    if (this->_levelForce >= 2) {
        return;
    }
    this->_levelForce += 1;
}

void Force::haveToShoot() noexcept
{
    if (this->isEquipped()) {
        this->_haveToShoot = true;
    }
}

void Force::stopShoot() noexcept
{
    this->_haveToShoot = false;
}

const bool &Force::getHaveIToShoot() const noexcept
{
    return (this->_haveToShoot);
}

sf::Clock &Force::getClockShoot() noexcept
{
    return (this->_clockShoot);
}

void Force::shootForwardForce(const float &initialDamage) noexcept
{
    this->_isShootForward = true;
    this->_isEquipped = false;
    this->_initialeDamage = initialDamage;
}

void Force::stopShootingForward() noexcept
{
    this->_isShootForward = false;
}

const bool &Force::isShootForward() const noexcept
{
    return (this->_isShootForward);
}

const float &Force::getInitialDamage() const noexcept
{
    return (this->_initialeDamage);
}

void Force::reattachedForce() noexcept
{
    if (this->_idBelong >= 0) {
        this->_isShootForward = false;
        this->_isEquipped = true;
    }
}
