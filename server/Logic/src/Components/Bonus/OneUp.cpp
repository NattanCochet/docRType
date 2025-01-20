/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** OneUp
*/

#include "../../../include/Components/Bonus/OneUp.hpp"

OneUp::OneUp(const std::size_t oneUp) : ABonus(), _oneUp(oneUp)
{
}

OneUp::~OneUp()
{
}

bool OneUp::activate(World &world, std::size_t myIndexEntity)
{
    Registry &r = world.getRegistry();

    std::optional<Vitality> &vit = r.get_components<Vitality>()[myIndexEntity];

    if (!vit.has_value()) {
        return (true);
    }
    vit->healEntity(this->_oneUp);
    return (true);
}
