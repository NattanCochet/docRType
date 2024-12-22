/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** VirtualKeyBoard
*/

#include "../include/VirtualKeyBoard.hpp"

VirtualKeyBoard::VirtualKeyBoard()
{
    _virtualKeyboard = {
        {CONTROL::UP, false},
        {CONTROL::DOWN, false},
        {CONTROL::LEFT, false},
        {CONTROL::RIGHT, false},
        {CONTROL::SHOOT, false},
        {CONTROL::FORCE, false},
        {CONTROL::START, false}
    };
    _isCharging = false;
}

VirtualKeyBoard::~VirtualKeyBoard()
{
}

std::unordered_map<VirtualKeyBoard::CONTROL, bool> &VirtualKeyBoard::getVirtualKeyboard() noexcept
{
    return (_virtualKeyboard);
}

void VirtualKeyBoard::changeValueKeyboard(VirtualKeyBoard::CONTROL key, bool isPressed) noexcept
{
    _virtualKeyboard[key] = isPressed;
}

bool VirtualKeyBoard::isKeyIsPressed(CONTROL key)
{
    return (_virtualKeyboard[key]);
}

bool VirtualKeyBoard::isCharging()
{
    return (this->_isCharging);
}

void VirtualKeyBoard::setIsCharging(bool isCharging)
{
    this->_isCharging = isCharging;
}
