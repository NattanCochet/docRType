/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** UpgradeForce
*/

#ifndef UPGRADEFORCE_HPP_
#define UPGRADEFORCE_HPP_
#include "../ABonus.hpp"
#include "../../ECS/World.hpp"

class UpgradeForce : public ABonus
{
  public:
    UpgradeForce();
    ~UpgradeForce();

    bool activate(World &world, std::size_t myIndexEntity) override;

  private:
};

#endif /* !UPGRADEFORCE_HPP_ */
