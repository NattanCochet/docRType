/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** MyClock
*/

#ifndef MYCLOCK_HPP_
#define MYCLOCK_HPP_
#include <SFML/System/Clock.hpp>

class MyClock
{
    public:
        MyClock();
        ~MyClock();
        sf::Time restart();
        sf::Time start();
        sf::Time pause();
        sf::Time restartAndPause();
        sf::Time getElapsedTime();

    private:
        sf::Clock _clock;
        sf::Time _start;
        sf::Time _pause;
        bool _isRunning;
};

#endif /* !MYCLOCK_HPP_ */
