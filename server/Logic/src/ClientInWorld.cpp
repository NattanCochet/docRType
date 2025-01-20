/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ClientInWorld
*/

#include "../include/ClientInWorld.hpp"

ClientInWorld::ClientInWorld() :
    _clientID(0), _currentLevel(0), _score(0), _maxScorePerLevel(), _name("Unkwown"), _isReady(false), _rowSkin(0)
{
}

ClientInWorld::ClientInWorld(std::size_t clientID, std::string name) :
    _clientID(clientID), _currentLevel(0), _score(0), _maxScorePerLevel(), _name(name), _isReady(false), _rowSkin(0)
{
}

ClientInWorld::~ClientInWorld()
{
}

std::size_t ClientInWorld::getClientID()
{
    return (this->_clientID);
}

int ClientInWorld::getScore()
{
    return (this->_score);
}

const std::size_t &ClientInWorld::getMaxScorePerLevel(const std::size_t &level) const
{
    if (level >= this->_maxScorePerLevel.size()) {
        throw ErrorKeyNotFound(std::to_string(level), "ClientInWorld::getMaxScorePerLevel");
    }
    return (this->_maxScorePerLevel[level]);
}

const std::string &ClientInWorld::getName() const noexcept
{
    return (this->_name);
}

void ClientInWorld::setClientID(const std::size_t &newClientID) noexcept
{
    this->_clientID = newClientID;
}

void ClientInWorld::addScore(const int scoreToAdd, const std::size_t scoringInLevel) noexcept
{
    if (this->_currentLevel != scoringInLevel) {
        this->saveScore();
        this->_score = 0;
        this->_currentLevel = scoringInLevel;
    }
    this->_score += scoreToAdd;
}

void ClientInWorld::saveScore() noexcept
{
    if (this->_currentLevel >= this->_maxScorePerLevel.size()) {
        this->_maxScorePerLevel.resize(this->_currentLevel + 1, 0);
    }
    if (this->_score > this->_maxScorePerLevel.at(this->_currentLevel)) {
        this->_maxScorePerLevel[this->_currentLevel] = this->_score;
    }
}

void ClientInWorld::setName(const std::string &newName) noexcept
{
    this->_name = newName;
}

void ClientInWorld::clientIsReady() noexcept
{
    this->_isReady = true;
}

void ClientInWorld::clientIsntReady() noexcept
{
    this->_isReady = false;
}

const bool &ClientInWorld::isReady() const noexcept
{
    return (this->_isReady);
}

void ClientInWorld::resetScore() noexcept
{
    this->_score = 0;
}

std::size_t &ClientInWorld::getRowSkin() noexcept
{
    return (this->_rowSkin);
}

void ClientInWorld::setRowSkin(const std::size_t rowSkin) noexcept
{
    this->_rowSkin = rowSkin % 5;
}
