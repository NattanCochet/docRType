/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Projectile
*/

#include "../../include/Components/Projectile.hpp"

Projectile::Projectile
    (
        float _damage, float _loadingTime, bool _isRebound,
        bool _canHoldCharging, float _reductionDamage, float _damageFallOff
    )
{
    this->_damage = _damage;
    this->_loadingTime = _loadingTime;
    this->_isRebound = _isRebound;
    this->_canHoldCharging = _canHoldCharging;
    this->_reductionDamage = _reductionDamage;
    this->_damageFallOff = _damageFallOff;
    this->_stack = 1;
}

Projectile::~Projectile()
{
}

void Projectile::setDamage(float newDmg) {
    _damage = newDmg;
}

void Projectile::setDamageFallOff(float newDmgFalloff) {
    _damageFallOff = newDmgFalloff;
}

void Projectile::setHoldCharging(bool newCharge) {
    _canHoldCharging = newCharge;
}

void Projectile::setIsRebound(bool newRebound) {
    _isRebound = newRebound;
}

void Projectile::setLoadingTime(float newLoadingTime) {
    _loadingTime = newLoadingTime;
}

void Projectile::setReductionDamage(float newDmgReduction) {
    _reductionDamage = newDmgReduction;
}

void Projectile::setStack(int newStack) {
    _stack = newStack;
}

float Projectile::getDamage(void) {
    return _damage;
}

float Projectile::getLoadingTime(void) {
    return _loadingTime;
}

float Projectile::getDmgFalloff(void) {
    return _damageFallOff;
}

float Projectile::getReductionDmg(void) {
    return _reductionDamage;
}

bool Projectile::getCanHoldCharge(void) {
    return _canHoldCharging;
}

bool Projectile::getRebound(void) {
    return _isRebound;
}

int Projectile::getStack(void) {
    return _stack;
}
