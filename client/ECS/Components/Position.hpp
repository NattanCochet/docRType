/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Position
*/

/**
 * @file Position.hpp
 * @brief Header file for the Position class.
 */

#pragma once
#ifndef POSITION_HPP_
#define POSITION_HPP_

#include <SFML/System.hpp>
#include <iostream>

/**
 * @class Position
 * @brief Class to manage 2D positions in the game.
 * 
 * This class represents a 2D position using `sf::Vector2f`. It allows storing
 * the current position and a default position, as well as modifying them.
 */
class Position {
    public:
        /**
         * @brief Default constructor for the Position class.
         */
        Position();

        /**
         * @brief Constructor for the Position class with an initial position.
         * @param pos The initial position as an `sf::Vector2f`.
         */
        Position(sf::Vector2f pos);

        /**
         * @brief Constructor for the Position class with an initial position as integer values.
         * @param x The x-coordinate of the initial position.
         * @param y The y-coordinate of the initial position.
         */
        Position(float x, float y);

        /**
         * @brief Destructor for the Position class.
         */
        ~Position();

        /**
         * @brief Gets the current position.
         * @return A reference to the current position as an `sf::Vector2f`.
         */
        sf::Vector2f &getPosition();

        /**
         * @brief Gets the default position.
         * @return A reference to the default position as an `sf::Vector2f`.
         */
        sf::Vector2f &getDefaultPosition();

        /**
         * @brief Sets the current position.
         * @param newPos The new position as an `sf::Vector2f`.
         */
        void setPosition(sf::Vector2f newPos);

        /**
         * @brief Sets the current position using integer coordinates.
         * @param x The new x-coordinate for the current position.
         * @param y The new y-coordinate for the current position.
         */
        void setPosition(int x, int y);

        /**
         * @brief Sets the default position.
         * @param newPos The new default position as an `sf::Vector2f`.
         */
        void setDefaultPosition(sf::Vector2f newPos);

        /**
         * @brief Sets the default position using integer coordinates.
         * @param x The new x-coordinate for the default position.
         * @param y The new y-coordinate for the default position.
         */
        void setDefaultPosition(int x, int y);

    protected:
    private:
        sf::Vector2f _pos; ///< Current position.
        sf::Vector2f _defaultPos; ///< Default position.
};

#endif /* !POSITION_HPP_ */
