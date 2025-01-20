/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Speed
*/

#ifndef SPEED_HPP_
#define SPEED_HPP_
#include "../ABonus.hpp"
#include "../../ECS/World.hpp"

class Speed : public ABonus
{
  public:
    Speed(const float speedUp);
    ~Speed();

    bool activate(World &world, std::size_t myIndexEntity) override;

  private:
    float _seepUp;
};

#endif /* !SPEED_HPP_ */
