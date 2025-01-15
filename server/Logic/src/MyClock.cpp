/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** MyClock
*/

#include "../include/MyClock.hpp"

MyClock::MyClock() : _isRunning(false), _start(sf::Time::Zero), _pause(sf::Time::Zero)
{
}

MyClock::~MyClock()
{
}

sf::Time MyClock::restart()
{
    sf::Time elapsed = getElapsedTime();
    _clock.restart();
    _start = sf::Time::Zero;
    _pause = sf::Time::Zero;
    _isRunning = true;
    return elapsed;
}

sf::Time MyClock::start()
{
    if (!_isRunning) {
        if (_pause != sf::Time::Zero) {
            _start = _clock.getElapsedTime() - _pause;
        } else {
            _start = _clock.getElapsedTime();
        }
        _isRunning = true;
    }
    return getElapsedTime();
}

sf::Time MyClock::pause()
{
    if (_isRunning) {
        _pause = _clock.getElapsedTime() - _start;
        _isRunning = false;
    }
    return _pause;
}

sf::Time MyClock::restartAndPause()
{
    sf::Time elapsed = restart();
    pause();
    return elapsed;
}

sf::Time MyClock::getElapsedTime()
{
    if (_isRunning) {
        return _clock.getElapsedTime() - _start;
    }
    return _pause;
}
