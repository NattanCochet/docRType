/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Position
*/

#pragma once
#ifndef POSITION_HPP_
#define POSITION_HPP_
#include "../Vector.hpp"
#include <SFML/System/Vector2.hpp>

/**
 * @class Position
 * @brief A class to represent and manage the position of an object.
 *
 * This class manages the position of an object using two `sf::Vector2f` objects:
 * one for the current position and one for the default position. It provides methods
 * to get and set the position values.
 */
class Position {
    public:
        /**
         * @brief Default constructor for the Position class.
         * Initializes the position to (0, 0) and the default position to (0, 0).
         */
        Position();

        /**
         * @brief Constructs a Position object with a specific position.
         *
         * @param pos The initial position as an `sf::Vector2f`.
         */
        Position(sf::Vector2f pos);

        /**
         * @brief Constructs a Position object with specific x and y coordinates.
         *
         * @param x The x-coordinate of the position.
         * @param y The y-coordinate of the position.
         */
        Position(int x, int y);

        /**
         * @brief Destructor for the Position class.
         */
        ~Position();

        /**
         * @brief Gets the current position of the object.
         *
         * @return A reference to the `sf::Vector2f` representing the current position.
         */
        sf::Vector2f &getPosition();

        /**
         * @brief Gets the default position of the object.
         *
         * @return A reference to the `sf::Vector2f` representing the default position.
         */
        sf::Vector2f &getDefaultPosition();

        /**
         * @brief Sets the current position to a new value.
         *
         * @param newPos The new position as an `sf::Vector2f`.
         */
        void setPosition(sf::Vector2f newPos);

        /**
         * @brief Sets the current position using specific x and y coordinates.
         *
         * @param x The new x-coordinate for the position.
         * @param y The new y-coordinate for the position.
         */
        void setPosition(int x, int y);

        /**
         * @brief Sets the default position to a new value.
         *
         * @param newPos The new default position as an `sf::Vector2f`.
         */
        void setDefaultPosition(sf::Vector2f newPos);

        /**
         * @brief Sets the default position using specific x and y coordinates.
         *
         * @param x The new x-coordinate for the default position.
         * @param y The new y-coordinate for the default position.
         */
        void setDefaultPosition(int x, int y);

    protected:
    private:
        sf::Vector2f _pos; ///< The current position of the object.
        sf::Vector2f _defaultPos; ///< The default position of the object.
};

#endif /* !POSITION_HPP_ */
