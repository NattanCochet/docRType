/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Area
*/

#include "../../include/Components/Area.hpp"

Area::Area(float radius, Vector<int, 2> position)
    : _radius(radius), _position(position)
{
}

Area::~Area()
{
}

const float &Area::getRadius() const noexcept
{
    return (this->_radius);
}

Vector<int, 2> &Area::getPosition() noexcept
{
    return (this->_position);
}

const bool Area::isInAreaOfEntity(const std::size_t &otherEntityID) const noexcept
{
    return std::binary_search(_collisionsByID.begin(), _collisionsByID.end(), otherEntityID);
}

const std::unordered_set<std::size_t> &Area::getAllEntityInArea() const noexcept
{
    return (this->_collisionsByID);
}

void Area::setRadius(const float &radius) noexcept
{
    this->_radius = radius;
}

void Area::setPostion(const Vector<int, 2> newPosition) noexcept
{
    this->_position = newPosition;
}

void Area::anEntityIsEnterArea(const std::size_t entityID) noexcept
{
    this->_collisionsByID.insert(entityID);
}

void Area::clearData() noexcept
{
    this->_collisionsByID.clear();
}
