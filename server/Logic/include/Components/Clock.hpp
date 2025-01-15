/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Clock
*/

/**
 * @file Clock.hpp
 * @brief Declaration of the Clock class, which manages multiple sf::Clock instances.
 */

#ifndef CLOCK_HPP_
#define CLOCK_HPP_

#include <unordered_map>
#include <string>
#include <SFML/System.hpp>
#include "../Error/ErrorKeyNotFound.hpp"
#include "../Error/ErrorKeyAlreadyExistInMap.hpp"

/**
 * @class Clock
 * @brief A utility class for managing multiple named `sf::Clock` instances.
 *
 * This class provides a convenient way to manage and access multiple `sf::Clock` objects
 * identified by unique string IDs. It includes error handling for duplicate keys and missing keys.
 */
class Clock {
    public:
        /**
         * @brief Default constructor for the Clock class.
         */
        Clock();

        /**
         * @brief Constructs a Clock object and initializes clocks with the provided keys.
         * 
         * @tparam Args Variadic template for string arguments representing clock IDs.
         * @param args A list of string IDs to initialize clocks.
         */
        template<typename ...Args>
        Clock(Args... args)
        {
            (((_mapClock[static_cast<std::string>(args)] = sf::Clock())), ...);
        }

        /**
         * @brief Destructor for the Clock class.
         */
        ~Clock();

        /**
         * @brief Adds a new clock with a specified ID.
         * 
         * @param idClock The unique string identifier for the clock.
         * 
         * @throw ErrorKeyAlreadyExistInMap If a clock with the specified ID already exists.
         */
        void addClock(const std::string &idClock);

        /**
         * @brief Retrieves a clock by its ID.
         * 
         * @param idClock The unique string identifier of the clock.
         * @return A reference to the `sf::Clock` object.
         * 
         * @throw ErrorKeyNotFound If no clock exists with the specified ID.
         */
        sf::Clock &getClock(const std::string &idClock);

    private:
        std::unordered_map<std::string, sf::Clock> _mapClock; /**< Map storing clocks identified by unique string IDs. */
};

#endif /* !CLOCK_HPP_ */
