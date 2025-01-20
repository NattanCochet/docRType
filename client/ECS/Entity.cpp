/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Entity
*/

#include "Entity.hpp"

Entity::operator std::size_t() const
{
    return this->id;
}
