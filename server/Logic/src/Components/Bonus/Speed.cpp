/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Speed
*/

#include "../../../include/Components/Bonus/Speed.hpp"

Speed::Speed(const float speedUp) : ABonus(), _seepUp(speedUp)
{
}

Speed::~Speed()
{
}

bool Speed::activate(World &world, std::size_t myIndexEntity)
{
    std::optional<Controllable> &controllable = world.getRegistry().get_components<Controllable>()[myIndexEntity];

    if (!controllable.has_value()) {
        return (true);
    }
    controllable->setSpeed(controllable->getSpeed() + this->_seepUp);
    return (true);
}
