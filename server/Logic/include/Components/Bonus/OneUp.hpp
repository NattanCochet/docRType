/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** OneUp
*/

#ifndef ONEUP_HPP_
#define ONEUP_HPP_
#include "../../ECS/World.hpp"
#include "../ABonus.hpp"

class OneUp : public ABonus
{
  public:
    OneUp(const std::size_t oneUp);
    ~OneUp();

    bool activate(World &world, std::size_t myIndexEntity) override;

  private:
    std::size_t _oneUp;
};

#endif /* !ONEUP_HPP_ */
