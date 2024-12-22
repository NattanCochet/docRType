/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Clock
*/

#ifndef CLOCK_HPP_
#define CLOCK_HPP_
#include <unordered_map>
#include <string>
#include <SFML/System.hpp>
#include "../Error/ErrorKeyNotFound.hpp"
#include "../Error/ErrorKeyAlreadyExistInMap.hpp"

class Clock {
    public:
        Clock();

        template<typename ...Args>
        Clock(Args... args)
        {
            (((_mapClock[std::to_string(args)] = sf::Clock())), ...);
        }

        ~Clock();

        void addClock(const std::string &idClock);

        sf::Clock &getClock(const std::string &idClock);

    private:
        std::unordered_map<std::string, sf::Clock> _mapClock;
};

#endif /* !CLOCK_HPP_ */
