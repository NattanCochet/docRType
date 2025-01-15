/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ClientInWorld
*/

#include "../include/ClientInWorld.hpp"

ClientInWorld::ClientInWorld() : _clientID(0), _score(0), _maxScore(-1), _name("Unkwown")
{
}

ClientInWorld::ClientInWorld(std::size_t clientID, std::string name, int maxScore)
    : _clientID(clientID), _score(0), _name(name), _maxScore(maxScore)
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

int ClientInWorld::getMaxScore()
{
    return (this->_maxScore);
}

std::string ClientInWorld::getName()
{
    return (this->_name);
}

void ClientInWorld::setClientID(std::size_t newClientID)
{
    this->_clientID = newClientID;
}

void ClientInWorld::setScore(int newScore)
{
    this->_score = newScore;
    if (this->_maxScore > 0 && this->_score > this->_maxScore) {
        this->_score = this->_maxScore;
    }
}

void ClientInWorld::addScore(int scoreToAdd)
{
    this->_score += scoreToAdd;
    if (this->_maxScore > 0 && this->_score > this->_maxScore) {
        this->_score = this->_maxScore;
    }
}

void ClientInWorld::setMaxScore(int newMaxScore)
{
    this->_maxScore = newMaxScore;
}

void ClientInWorld::setName(std::string newName)
{
    this->_name = newName;
}
