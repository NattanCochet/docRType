/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Controllable
*/

#pragma once
#ifndef CONTROLLABLE_HPP_
#define CONTROLLABLE_HPP_
#include "../VirtualKeyBoard.hpp"
#include <iostream>

/**
 * @class Controllable
 * @brief A class representing an entity that can be controlled in the system.
 *
 * The Controllable class holds the client ID and provides methods to get and set it.
 * This class can be used for controlling entities like players or other interactive objects.
 */
class Controllable {
    public:
        /**
         * @brief Constructor for the Controllable class.
         *
         * Initializes the Controllable object with a given client ID.
         * @param clientID The ID of the client controlling the entity.
         */
        Controllable(std::size_t clientID);

        /**
         * @brief Destructor for the Controllable class.
         *
         * Cleans up the resources used by the Controllable object.
         */
        ~Controllable();

        /**
         * @brief Gets the client ID of the controllable entity.
         *
         * This method returns the client ID associated with the controllable entity.
         * @return The client ID.
         */
        std::size_t getClientID() const noexcept;

        /**
         * @brief Sets the client ID for the controllable entity.
         *
         * This method allows updating the client ID of the controllable entity.
         * @param clientID The new client ID to be set.
         */
        void setClientID(const std::size_t &clientID) noexcept;

    private:
        /**
         * @brief The client ID associated with the controllable entity.
         *
         * This private member holds the client ID that uniquely identifies the controller of this entity.
         */
        std::size_t _clientID;
};

#endif /* !CONTROLLABLE_HPP_ */
