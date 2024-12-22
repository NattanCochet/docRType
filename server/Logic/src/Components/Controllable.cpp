/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Controllable
*/

#include "../../include/Components/Controllable.hpp"

Controllable::Controllable(std::size_t clientID) : _clientID(clientID)
{
}

Controllable::~Controllable()
{
}

std::size_t Controllable::getClientID() const noexcept
{
    return (_clientID);
}

void Controllable::setClientID(const std::size_t &clientID) noexcept
{
    _clientID = clientID;
}
