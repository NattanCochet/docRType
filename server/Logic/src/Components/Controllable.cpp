/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Controllable
*/

#include "../../include/Components/Controllable.hpp"

Controllable::Controllable(bool isPlayer, std::size_t clientID)
    : _isPlayer(isPlayer), _clientID(clientID), _keyBoard()
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

const bool Controllable::getIsPlayer() const noexcept
{
    return (this->_isPlayer);
}

void Controllable::setIsPlayer(const bool &isPlayer) noexcept
{
    this->_isPlayer = isPlayer;
}

VirtualKeyBoard &Controllable::getVirtualKeyboard() noexcept
{
    return (this->_keyBoard);
}
