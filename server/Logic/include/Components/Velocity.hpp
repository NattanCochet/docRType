/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Velocity
*/

#pragma once
#ifndef VELOCITY_HPP_
#define VELOCITY_HPP_
#include "../Vector.hpp"
#include <SFML/System/Vector2.hpp>

/**
 * @class Velocity
 * @brief Represents the velocity of an object, defined by its speed, time duration, and coefficient.
 *
 * The `Velocity` class encapsulates the velocity of an object, which consists of its speed (as a 2D vector),
 * the time duration over which the velocity is applied, and a coefficient that might represent any scaling factor
 * such as friction or resistance.
 */
class Velocity {
    public:
        /**
         * @brief Default constructor that initializes the velocity to default values.
         *
         * The default constructor initializes the speed to (0, 0), the seconds to 0.0f, and the coefficient to 1.0f.
         */
        Velocity();

        /**
         * @brief Constructor that initializes the velocity with given speed, time, and coefficient.
         *
         * @param speed The speed of the object as an `sf::Vector2i` (2D vector).
         * @param seconds The time duration the velocity is applied for.
         * @param coeff The coefficient that might scale the velocity (e.g., friction).
         */
        Velocity(sf::Vector2i speed, float seconds, float coeff);

        /**
         * @brief Constructor that initializes the velocity with given x and y speed components, time, and coefficient.
         *
         * @param xSpeed The speed in the x-direction.
         * @param ySpeed The speed in the y-direction.
         * @param seconds The time duration the velocity is applied for.
         * @param coeff The coefficient that might scale the velocity (e.g., friction).
         */
        Velocity(int xSpeed, int ySpeed, float seconds, float coeff);

        /**
         * @brief Destructor.
         *
         * The destructor does not perform any specific actions as no dynamic memory is allocated for this class.
         */
        ~Velocity();

        /**
         * @brief Retrieves the speed (as an `sf::Vector2i`).
         *
         * @return A reference to the `sf::Vector2i` representing the speed of the object.
         */
        sf::Vector2i &getSpeed();

        /**
         * @brief Retrieves the time duration (seconds) for which the velocity is applied.
         *
         * @return A reference to the float representing the duration in seconds.
         */
        float &getSeconds();

        /**
         * @brief Retrieves the coefficient that may scale the velocity.
         *
         * @return A reference to the float representing the coefficient (e.g., friction).
         */
        float &getCoeff();

        /**
         * @brief Sets a new speed for the object.
         *
         * @param newSpeed The new speed as an `sf::Vector2i`.
         */
        void setSpeed(sf::Vector2i newSpeed);

        /**
         * @brief Sets a new speed for the object by specifying the x and y components.
         *
         * @param newXSpeed The new speed in the x-direction.
         * @param newYSpeed The new speed in the y-direction.
         */
        void setSpeed(int newXSpeed, int newYSpeed);

        /**
         * @brief Sets a new time duration for the velocity.
         *
         * @param newSeconds The new time duration in seconds.
         */
        void setSeconds(float newSeconds);

        /**
         * @brief Sets a new coefficient for the velocity.
         *
         * @param newCoeff The new coefficient (e.g., friction).
         */
        void setCoeff(float newCoeff);

    protected:
    private:
        sf::Vector2i _speed; ///< The speed of the object as an `sf::Vector2i`.
        float _seconds; ///< The time duration for which the velocity is applied.
        float _coeff; ///< The coefficient (e.g., friction) that scales the velocity.
};

#endif /* !VELOCITY_HPP_ */
