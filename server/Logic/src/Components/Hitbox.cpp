/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Hitbox
*/

#include "../../include/Components/Hitbox.hpp"

Hitbox::Hitbox(TYPE type, Vector<int, 2> position, Vector<int, 2> size, float rotation)
    : _type(type), _position(position), _size(size)
{
    if (rotation > 360 || rotation < -360) {
        _rotation = 0.0;
    } else {
        _rotation = rotation;
    }
}

Hitbox::Hitbox()
{
}

Hitbox::~Hitbox()
{
}

Hitbox::TYPE Hitbox::getType() const
{
    return (this->_type);
}

Vector<int, 2> Hitbox::getPosition() const
{
    return (this->_position);
}

Vector<int, 2> Hitbox::getSize() const
{
    return (this->_size);
}

std::array<bool, 8> Hitbox::getEightAngleCollisionByID(std::size_t id)
{
    if (!this->_eightAnglesCollisionByID.contains(id)) {
        throw ErrorKeyNotFound(std::to_string(id), "Hitbox::getEightAngleCollisionByID");
    }
    return (this->_eightAnglesCollisionByID[id]);
}

float Hitbox::getRotation() const
{
    return (this->_rotation);
}

void Hitbox::setType(TYPE newType)
{
    this->_type = newType;
}

void Hitbox::setPosition(Vector<int, 2> newPosition)
{
    this->_position = newPosition;
}

void Hitbox::setPosition(int newXPosition, int newYPosition)
{
    this->_position = Vector<int, 2>(newXPosition, newYPosition);
}

void Hitbox::setSize(Vector<int, 2> newSize)
{
    this->_size = newSize;
}

void Hitbox::setSize(int newXSize, int newYSize)
{
    this->_size = Vector<int, 2>(newXSize, newYSize);
}

void Hitbox::setRotation(float newRotation)
{
    if (newRotation > 360 || newRotation < -360) {
        this->_rotation = 0.0;
    } else {
        this->_rotation = newRotation;
    }
}

void Hitbox::addCollisionWithID(std::size_t id, std::array<bool, 8> eightAngleCollisionByID)
{
    this->_eightAnglesCollisionByID[id] = eightAngleCollisionByID;
}

bool Hitbox::isCollisionWithID(std::size_t id)
{
    if (!this->_eightAnglesCollisionByID.contains(id)) {
        throw ErrorKeyNotFound(std::to_string(id), "Hitbox::isCollisionWithID");
    }
    std::array<bool, 8> eightAnglesCollisionBy = this->_eightAnglesCollisionByID[id];
    for (bool isCollision : eightAnglesCollisionBy) {
        if (isCollision) {
            return (true);
        }
    }
    return (false);
}

bool Hitbox::isCollisionWithIDInDirection(std::size_t id, DIRECTION direction)
{
    if (!this->_eightAnglesCollisionByID.contains(id)) {
        throw ErrorKeyNotFound(std::to_string(id), "Hitbox::isCollisionWithID");
    }
    return (this->_eightAnglesCollisionByID[id][direction]);
}

bool Hitbox::isCollision() const
{
    for (
        std::map<std::size_t, std::array<bool, 8>>::const_iterator it = this->_eightAnglesCollisionByID.begin();
        it != this->_eightAnglesCollisionByID.end();
        it++
    )
    {
        for (bool result : it->second) {
            if (result) {
                return (true);
            }
        }
    }
    return (false);
}

bool Hitbox::isCollisionInDirection(DIRECTION direction) const
{
    for (
        std::map<std::size_t, std::array<bool, 8>>::const_iterator it = this->_eightAnglesCollisionByID.begin();
        it != this->_eightAnglesCollisionByID.end();
        it++
    )
    {
        if (it->second[direction]) {
            return (true);
        }
    }
    return (false);
}
