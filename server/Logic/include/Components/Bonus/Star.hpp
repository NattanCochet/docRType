/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Star
*/

#ifndef STAR_HPP_
#define STAR_HPP_
#include "../../ECS/World.hpp"
#include "../../MyClock.hpp"
#include "../ABonus.hpp"

class Star : public ABonus
{
  public:
    Star(const float timeForInvincibility);
    ~Star();

    bool activate(World &world, std::size_t myIndexEntity) override;

  private:
    MyClock _clockForStar;
    float _time;
    bool _isAlreadyRestart;
};

#endif /* !STAR_HPP_ */
