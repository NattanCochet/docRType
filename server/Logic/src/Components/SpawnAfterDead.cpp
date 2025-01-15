/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** SpawnAfterDead
*/

#include "../../include/Components/SpawnAfterDead.hpp"

SpawnAfterDead::SpawnAfterDead(std::size_t idBeforeDead)
    : _idBeforeDead(idBeforeDead), _isDead(false)
{
}

SpawnAfterDead::~SpawnAfterDead()
{
}

const std::size_t &SpawnAfterDead::getIdBeforeDead()
{
    return (this->_idBeforeDead);
}

void SpawnAfterDead::setIdBeforeDead(const std::size_t &newID)
{
    this->_idBeforeDead = newID;
}

const bool &SpawnAfterDead::getIsDead()
{
    return (this->_isDead);
}

void SpawnAfterDead::entityIsDead()
{
    this->_isDead = true;
}
