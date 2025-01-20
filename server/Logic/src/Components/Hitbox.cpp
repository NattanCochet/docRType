/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Hitbox
*/

#include "../../include/Components/Hitbox.hpp"

Hitbox::RectHitbox::RectHitbox(const TYPE &type, const float &XHitbox, const float &YHitbox, const int &widthHitbox,
    const int &heightHitbox, const float &rotation, const bool &isActivate) :
    type(type), XHitbox(XHitbox), YHitbox(YHitbox), widthHitbox(widthHitbox), heightHitbox(heightHitbox),
    rotation(rotation), isActivate(isActivate)
{
}

Hitbox::RectHitbox::RectHitbox(const TYPE &type, const sf::Vector2f &position, const int &widthHitbox,
    const int &heightHitbox, const float &rotation, const bool &isActivate) :
    type(type), XHitbox(position.x), YHitbox(position.y), widthHitbox(widthHitbox), heightHitbox(heightHitbox),
    rotation(rotation), isActivate(isActivate)
{
}

Hitbox::RectHitbox::~RectHitbox()
{
}

Hitbox::Hitbox::Hitbox(const sf::Vector2f &position, const std::vector<RectHitbox> &hitboxs,
    const std::size_t &idBelong, const TEAM &isInPlayerTeam) :
    _positions(position), _hitboxs(), _idBelong(idBelong), _team(isInPlayerTeam), _sizeVectorHitboxs(hitboxs.size())
{
    if (this->_sizeVectorHitboxs == 0) {
        throw ErrorNoObject("std::vector<RectHitbox> &hitboxs", "Hitbox::Hitbox::Hitbox");
    }
    this->_hitboxs.reserve(this->_sizeVectorHitboxs);
    this->_hitboxs = hitboxs;
    this->_eightAnglesCollisionByIDAndHitboxs.resize(this->_sizeVectorHitboxs);
}

Hitbox::Hitbox::Hitbox(const float &XEntity, const float &YEntity, const std::vector<RectHitbox> &hitboxs,
    const std::size_t &idBelong, const TEAM &isInPlayerTeam) :
    _positions(XEntity, YEntity), _hitboxs(), _idBelong(idBelong), _team(isInPlayerTeam),
    _sizeVectorHitboxs(hitboxs.size())
{
    if (this->_sizeVectorHitboxs == 0) {
        throw ErrorNoObject("std::vector<RectHitbox> &hitboxs", "Hitbox::Hitbox::Hitbox");
    }
    this->_hitboxs.reserve(this->_sizeVectorHitboxs);
    this->_hitboxs = hitboxs;
    this->_eightAnglesCollisionByIDAndHitboxs.resize(this->_sizeVectorHitboxs);
}

Hitbox::Hitbox::~Hitbox()
{
}

Hitbox::TYPE Hitbox::Hitbox::getType(const std::size_t &indexHitbox) const
{
    if (indexHitbox >= this->_sizeVectorHitboxs) {
        throw ErrorKeyNotFound(std::to_string(indexHitbox), "Hitbox::Hitbox::getType");
    }
    return (this->_hitboxs[indexHitbox].type);
}

sf::Vector2f &Hitbox::Hitbox::getPosition() noexcept
{
    return (this->_positions);
}

sf::Vector2f Hitbox::Hitbox::getPositionHitbox(const std::size_t &indexHitbox) const
{
    if (indexHitbox >= this->_sizeVectorHitboxs) {
        throw ErrorKeyNotFound(std::to_string(indexHitbox), "Hitbox::Hitbox::getPositionHitbox");
    }
    return (sf::Vector2f(this->_hitboxs[indexHitbox].XHitbox, this->_hitboxs[indexHitbox].YHitbox));
}

sf::Vector2i Hitbox::Hitbox::getSizeHitbox(const std::size_t &indexHitbox) const
{
    if (indexHitbox >= this->_sizeVectorHitboxs) {
        throw ErrorKeyNotFound(std::to_string(indexHitbox), "Hitbox::Hitbox::getSizeHitbox");
    }
    return (sf::Vector2i(this->_hitboxs[indexHitbox].widthHitbox, this->_hitboxs[indexHitbox].heightHitbox));
}

std::array<bool, 8> Hitbox::Hitbox::getEightAngleCollisionByID(const std::size_t &indexHitbox, const std::size_t &id)
{
    if (indexHitbox >= this->_sizeVectorHitboxs) {
        throw ErrorKeyNotFound(std::to_string(indexHitbox), "Hitbox::Hitbox::getEightAngleCollisionByID");
    }
    if (!this->_eightAnglesCollisionByIDAndHitboxs[indexHitbox].contains(id)) {
        throw ErrorKeyNotFound(std::to_string(id), "Hitbox::Hitbox::getEightAngleCollisionByID");
    }
    return (this->_eightAnglesCollisionByIDAndHitboxs[indexHitbox][id]);
}

const float &Hitbox::Hitbox::getRotation(const std::size_t &indexHitbox) const
{
    if (indexHitbox >= this->_sizeVectorHitboxs) {
        throw ErrorKeyNotFound(std::to_string(indexHitbox), "Hitbox::Hitbox::getRotation");
    }
    return (this->_hitboxs[indexHitbox].rotation);
}

Hitbox::RectHitbox &Hitbox::Hitbox::getDataOfHitbox(const std::size_t &indexHitbox)
{
    if (indexHitbox >= this->_sizeVectorHitboxs) {
        throw ErrorKeyNotFound(std::to_string(indexHitbox), "Hitbox::Hitbox::getDataOfHitbox");
    }
    return (this->_hitboxs[indexHitbox]);
}

const Hitbox::TEAM &Hitbox::Hitbox::getTeam() const noexcept
{
    return (this->_team);
}

const std::size_t &Hitbox::Hitbox::getEntityID() const noexcept
{
    return (this->_idBelong);
}

void Hitbox::Hitbox::setType(const std::size_t &indexHitbox, const TYPE &newType)
{
    if (indexHitbox >= this->_sizeVectorHitboxs) {
        throw ErrorKeyNotFound(std::to_string(indexHitbox), "Hitbox::Hitbox::setType");
    }
    this->_hitboxs[indexHitbox].type = newType;
}

void Hitbox::Hitbox::setPosition(const sf::Vector2f &newPosition) noexcept
{
    this->_positions = newPosition;
}

void Hitbox::Hitbox::setPosition(const float &newXPosition, const float &newYPosition) noexcept
{
    this->_positions = sf::Vector2f(newXPosition, newYPosition);
}

void Hitbox::Hitbox::setPositionHitbox(const std::size_t indexHitbox, const sf::Vector2f &newPosition)
{
    if (indexHitbox >= this->_sizeVectorHitboxs) {
        throw ErrorKeyNotFound(std::to_string(indexHitbox), "Hitbox::Hitbox::setPositionHitbox");
    }
    this->_hitboxs[indexHitbox].XHitbox = newPosition.x;
    this->_hitboxs[indexHitbox].YHitbox = newPosition.y;
}

void Hitbox::Hitbox::setPositionHitbox(
    const std::size_t &indexHitbox, const float &newXPosition, const float &newYPosition)
{
    if (indexHitbox >= this->_sizeVectorHitboxs) {
        throw ErrorKeyNotFound(std::to_string(indexHitbox), "Hitbox::Hitbox::setPositionHitbox");
    }
    this->_hitboxs[indexHitbox].XHitbox = newXPosition;
    this->_hitboxs[indexHitbox].YHitbox = newYPosition;
}

void Hitbox::Hitbox::setSizeHitbox(const std::size_t &indexHitbox, const sf::Vector2i &newSize)
{
    if (indexHitbox >= this->_sizeVectorHitboxs) {
        throw ErrorKeyNotFound(std::to_string(indexHitbox), "Hitbox::Hitbox::setSizeHitbox");
    }
    this->_hitboxs[indexHitbox].widthHitbox = newSize.x;
    this->_hitboxs[indexHitbox].heightHitbox = newSize.y;
}

void Hitbox::Hitbox::setSizeHitbox(const std::size_t &indexHitbox, const int &newXSize, const int &newYSize)
{
    if (indexHitbox >= this->_sizeVectorHitboxs) {
        throw ErrorKeyNotFound(std::to_string(indexHitbox), "Hitbox::Hitbox::setSizeHitbox");
    }
    this->_hitboxs[indexHitbox].widthHitbox = newXSize;
    this->_hitboxs[indexHitbox].heightHitbox = newYSize;
}

void Hitbox::Hitbox::setRotationHitbox(const std::size_t &indexHitbox, const float &newRotation)
{
    if (indexHitbox >= this->_sizeVectorHitboxs) {
        throw ErrorKeyNotFound(std::to_string(indexHitbox), "Hitbox::Hitbox::setRotationHitbox");
    }
    this->_hitboxs[indexHitbox].rotation = newRotation;
}

void Hitbox::Hitbox::setTeam(const TEAM &newTeam) noexcept
{
    this->_team = newTeam;
}

void Hitbox::Hitbox::setEntityID(const std::size_t &newEntityID) noexcept
{
    this->_idBelong = newEntityID;
}

void Hitbox::Hitbox::addCollisionWithIDAndHitbox(
    const std::size_t &indexHitbox, const std::size_t &id, const std::array<bool, 8> &collisionData)
{
    if (indexHitbox >= this->_sizeVectorHitboxs) {
        throw ErrorKeyNotFound(std::to_string(indexHitbox), "Hitbox::Hitbox::addCollisionWithIDAndHitbox");
    }
    this->_eightAnglesCollisionByIDAndHitboxs[indexHitbox][id] = collisionData;
}

void Hitbox::Hitbox::resetCollisions() noexcept
{
    for (std::map<std::size_t, std::array<bool, 8>> &eightAnglesCollisionByID :
        this->_eightAnglesCollisionByIDAndHitboxs) {
        eightAnglesCollisionByID.clear();
    }
}

void Hitbox::Hitbox::deleteCollisions(const std::size_t &indexHitbox, const std::size_t &id)
{
    if (indexHitbox >= this->_sizeVectorHitboxs) {
        throw ErrorKeyNotFound(std::to_string(indexHitbox), "Hitbox::Hitbox::deleteCollisions");
    }
    if (!this->_eightAnglesCollisionByIDAndHitboxs[indexHitbox].contains(id)) {
        throw ErrorKeyNotFound(std::to_string(id), "Hitbox::getEightAngleCollisionByID");
    }
    this->_eightAnglesCollisionByIDAndHitboxs[indexHitbox].erase(id);
}

bool Hitbox::Hitbox::isCollisionWithID(const std::size_t &id) const noexcept
{
    for (const std::map<std::size_t, std::array<bool, 8>> &eightAnglesCollisionByID :
        this->_eightAnglesCollisionByIDAndHitboxs) {
        if (!eightAnglesCollisionByID.contains(id)) {
            continue;
        }
        for (const bool &value : eightAnglesCollisionByID.at(id)) {
            if (value) {
                return (true);
            }
        }
    }
    return (false);
}

bool Hitbox::Hitbox::isCollisionWithID(const std::size_t &indexHitbox, const std::size_t &id) const noexcept
{
    if (indexHitbox >= this->_sizeVectorHitboxs) {
        return (false);
    }
    if (!this->_eightAnglesCollisionByIDAndHitboxs[indexHitbox].contains(id)) {
        return (false);
    }
    for (const bool &value : this->_eightAnglesCollisionByIDAndHitboxs[indexHitbox].at(id)) {
        if (value) {
            return (true);
        }
    }
    return (false);
}

bool Hitbox::Hitbox::isCollision() const noexcept
{
    for (const std::map<std::size_t, std::array<bool, 8>> &eightAnglesCollisionByID :
        this->_eightAnglesCollisionByIDAndHitboxs) {
        for (const std::pair<const std::size_t, std::array<bool, 8>> &eightAnglesCollision : eightAnglesCollisionByID) {
            for (const bool &value : eightAnglesCollision.second) {
                if (value) {
                    return (true);
                }
            }
        }
    }
    return (false);
}

bool Hitbox::Hitbox::isCollisionInDirection(const DIRECTION &direction) const noexcept
{
    for (const std::map<std::size_t, std::array<bool, 8>> &eightAnglesCollisionByID :
        this->_eightAnglesCollisionByIDAndHitboxs) {
        for (const std::pair<const std::size_t, std::array<bool, 8>> &eightAnglesCollision : eightAnglesCollisionByID) {
            if (eightAnglesCollision.second[direction]) {
                return (true);
            }
        }
    }
    return (false);
}

bool Hitbox::Hitbox::isCollisionInDirection(const std::size_t &indexHitbox, const DIRECTION &direction) const noexcept
{
    if (indexHitbox >= this->_sizeVectorHitboxs) {
        return (false);
    }
    for (const std::pair<const std::size_t, std::array<bool, 8>> &eightAnglesCollision :
        this->_eightAnglesCollisionByIDAndHitboxs[indexHitbox]) {
        if (eightAnglesCollision.second[direction]) {
            return (true);
        }
    }
    return (false);
}

bool Hitbox::Hitbox::isCollisionWithIDInDirection(const std::size_t &id, const DIRECTION &direction) const noexcept
{
    for (const std::map<std::size_t, std::array<bool, 8>> &eightAnglesCollisionByID :
        this->_eightAnglesCollisionByIDAndHitboxs) {
        if (!eightAnglesCollisionByID.contains(id)) {
            continue;
        }
        if (eightAnglesCollisionByID.at(id)[direction]) {
            return (true);
        }
    }
    return (false);
}

bool Hitbox::Hitbox::isCollisionWithIDInDirection(
    const std::size_t &indexHitbox, const std::size_t &id, const DIRECTION &direction) const noexcept
{
    if (indexHitbox >= this->_sizeVectorHitboxs) {
        return (false);
    }
    if (!this->_eightAnglesCollisionByIDAndHitboxs[indexHitbox].contains(id)) {
        return (false);
    }
    return (this->_eightAnglesCollisionByIDAndHitboxs[indexHitbox].at(id)[direction]);
}

std::vector<std::size_t> Hitbox::Hitbox::getAllCollisionIDs() const noexcept
{
    std::vector<std::size_t> res;
    for (const std::map<std::size_t, std::array<bool, 8>> &eightAnglesCollisionByID :
        this->_eightAnglesCollisionByIDAndHitboxs) {
        for (const std::pair<const std::size_t, std::array<bool, 8>> &eightAnglesCollision : eightAnglesCollisionByID) {
            res.emplace_back(eightAnglesCollision.first);
        }
    }
    return (res);
}

std::vector<Hitbox::RectHitbox> &Hitbox::Hitbox::getAllHitboxs() noexcept
{
    return (this->_hitboxs);
}

const std::size_t &Hitbox::Hitbox::getNbrHitboxs() const noexcept
{
    return (this->_sizeVectorHitboxs);
}

const bool Hitbox::Hitbox::getIsActivate(const std::size_t &indexHitbox) const
{
    if (indexHitbox >= this->_sizeVectorHitboxs) {
        return (false);
    }
    return (this->_hitboxs[indexHitbox].isActivate);
}

void Hitbox::Hitbox::setIsActivate(const std::size_t &indexHitbox, const bool &isActivate)
{
    if (indexHitbox >= this->_sizeVectorHitboxs) {
        throw ErrorKeyNotFound(std::to_string(indexHitbox), "Hitbox::Hitbox::setIsActivate");
    }
    this->_hitboxs[indexHitbox].isActivate = isActivate;
}

const std::vector<std::size_t> Hitbox::Hitbox::getHitboxsIndexInCollisions() const noexcept
{
    std::vector<std::size_t> res;
    res.reserve(this->_sizeVectorHitboxs);

    std::size_t index = 0;

    for (const std::map<std::size_t, std::array<bool, 8>> &eachCollision : this->_eightAnglesCollisionByIDAndHitboxs) {
        bool found = false;
        for (const std::pair<const std::size_t, std::array<bool, 8>> &eightAnglesCollision : eachCollision) {
            for (const bool &value : eightAnglesCollision.second) {
                if (value) {
                    res.emplace_back(index);
                    found = true;
                    break;
                }
            }
            if (found)
                break;
        }
        index += 1;
    }
    return (res);
}

const std::size_t Hitbox::Hitbox::getHitboxsIndexInCollisionsWithEntityID(std::size_t entityID) const
{
    std::size_t index = 0;

    for (const std::map<std::size_t, std::array<bool, 8>> &eachCollision : this->_eightAnglesCollisionByIDAndHitboxs) {
        for (const std::pair<const std::size_t, std::array<bool, 8>> &eightAnglesCollision : eachCollision) {
            if (eightAnglesCollision.first == entityID) {
                return (index);
            }
        }
        index += 1;
    }
    throw ErrorKeyNotFound(std::to_string(entityID), "Hitbox::Hitbox::getHitboxsIndexInCollisionsWithEntityID");
}
