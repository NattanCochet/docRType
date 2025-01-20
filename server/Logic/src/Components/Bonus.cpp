/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Bonus
*/

#include "../../include/Components/Bonus.hpp"

Bonus::Bonus(int id, std::shared_ptr<ABonus> bonus) : _id(id), _bonus(bonus)
{
}

Bonus::~Bonus()
{
}

int Bonus::getId()
{
    return (this->_id);
}

void Bonus::setId(int newId)
{
    this->_id = newId;
}

std::shared_ptr<ABonus> &Bonus::getBonus()
{
    return (this->_bonus);
}

void Bonus::setBonus(std::shared_ptr<ABonus> newBonus)
{
    this->_bonus = newBonus;
}
