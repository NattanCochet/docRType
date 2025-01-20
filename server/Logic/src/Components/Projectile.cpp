/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Projectile
*/

#include "../../include/Components/Projectile.hpp"

Projectile::Projectile
    (
        float damage, bool isRebound, bool canHoldCharging, float damageFallOff,
        std::size_t entityIDBelong
    )
{
    this->_damage = damage;
    this->_isRebound = isRebound;
    this->_canHoldCharging = canHoldCharging;
    this->_damageFallOff = damageFallOff;
    this->_entityIDBelong = entityIDBelong;
    this->_stack = 1;
}

Projectile::~Projectile()
{
}

void Projectile::setDamage(float newDmg)
{
    this->_damage = newDmg;
}

void Projectile::setDamageFallOff(float newDmgFalloff)
{
    this->_damageFallOff = newDmgFalloff;
}

void Projectile::setHoldCharging(bool newCharge)
{
    this->_canHoldCharging = newCharge;
}

void Projectile::setIsRebound(bool newRebound)
{
    this->_isRebound = newRebound;
}

void Projectile::setEntityIDBelong(std::size_t newID)
{
    this->_entityIDBelong = newID;
}

void Projectile::setStack(int newStack)
{
    this->_stack = newStack;
}

float Projectile::getDamage(void)
{
    return this->_damage;
}

std::size_t Projectile::getEntityIDBelong(void)
{
    return this->_entityIDBelong;
}

float Projectile::getDmgFalloff(void)
{
    return this->_damageFallOff;
}

bool Projectile::getCanHoldCharge(void)
{
    return this->_canHoldCharging;
}

bool Projectile::getRebound(void)
{
    return this->_isRebound;
}

int Projectile::getStack(void)
{
    return this->_stack;
}

void Projectile::addEntityIDAlreadyTouch(const std::size_t &entityID) noexcept
{
    this->_entityIDAlreadyTouch.push_back(entityID);
}

const bool Projectile::isEntityIDAlreadyTouch(const std::size_t &entityID) noexcept
{
    for (std::size_t id : this->_entityIDAlreadyTouch) {
        if (id == entityID) {
            return (true);
        }
    }
    return (false);
}

void Projectile::clearEntityIDAlreadyTouch() noexcept
{
    this->_entityIDAlreadyTouch.clear();
}
