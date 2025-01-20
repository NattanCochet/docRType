/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Controllable
*/

/**
 * @file Controllable.hpp
 * @brief Header file for the Controllable class.
 */

#pragma once
#ifndef CONTROLLABLE_HPP_
#define CONTROLLABLE_HPP_
#include "../World.hpp"
#include "ControlsEnum.hpp"

/**
 * @class Controllable
 * @brief Base class representing objects that can be controlled.
 *
 * This class serves as a base class for objects that can be controlled
 * within the game, though it does not define specific control mechanisms.
 * It can be extended by other classes that define more concrete control behavior.
 */

class Network;

class Controllable
{
public:
    /**
     * @brief Default constructor for the Controllable class.
     */
    Controllable();

    /**
     * @brief Destructor for the Controllable class.
     */
    ~Controllable();

    void updateControl(World &world, sf::Keyboard::Key key, bool pressed, std::size_t index, Network *network);

    void changePosition(Position &pos);

private:
    std::map<CONTROL, bool> _keys;
};

#endif /* !CONTROLLABLE_HPP_ */
