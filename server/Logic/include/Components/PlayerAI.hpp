/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** PlayerAI
*/

#ifndef PLAYERAI_HPP_
#define PLAYERAI_HPP_
#include <SFML/System.hpp>

class PlayerAI
{
  public:
    PlayerAI();
    ~PlayerAI();
    float getDelay();
    float getShootDelay();
    float getBigShootDelay();
    sf::Clock &getMoveClock();
    sf::Clock &getShootClock();
    sf::Clock &getBigShoot();
    int getStacks();
    void setStacks(int newStacks);

  private:
    sf::Clock _move;
    sf::Clock _shoot;
    sf::Clock _bigShoot;
    float _delay = 0.7f;
    float _shootDelay = 0.3f;
    float _bigShootDelay = 4.0f;
    int _stacks = 0;
};

#endif /* !PLAYERAI_HPP_ */
