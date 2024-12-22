/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** *
*/

#include "../../include/Components/Vitality.hpp"

Vitality::Vitality() : _nbrLife(0), _nbrLifeMax(0), _defaultLife(0)
{
}

Vitality::Vitality(int nbrLife, int nbrLifeMax) : _nbrLife(nbrLife), _nbrLifeMax(nbrLifeMax), _defaultLife(nbrLife)
{
}

int Vitality::getLife() const
{
    return (this->_nbrLife);
}

int Vitality::getDefaultLife() const
{
    return (this->_defaultLife);
}

void Vitality::setNewLife(int newLife, int nbrLifeMax)
{
    _nbrLife = newLife;
    _defaultLife = newLife;
    _nbrLifeMax = nbrLifeMax;
}

void Vitality::healEntity(int heal)
{
    _nbrLife += heal;
    if (_nbrLifeMax >= 0 && _nbrLife > _nbrLifeMax) {
        _nbrLife = _nbrLifeMax;
    }
}

void Vitality::damageEntity(int damage)
{
    _nbrLife -= damage;
}

bool Vitality::isDead() const
{
    return (_nbrLife <= 0);
}
