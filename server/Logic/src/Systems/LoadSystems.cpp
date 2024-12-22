/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** LoadSystems
*/

#include "../../include/Systems.hpp"

Systems::Systems()
{
}

Systems::~Systems()
{
}

void Systems::loadSystemsInWorld(World &world)
{
    Registry &r = world.getRegistry();
    r.register_systems(this->vitalitySystem);
    r.register_systems(this->velocitySystem);
    r.register_systems(this->damageSystem);
    r.register_systems(this->controllableSystem);
    r.register_systems(this->linearSystem);
    r.register_systems(this->hitboxSystem);
    r.register_systems(this->drawableSystem);
    r.register_systems(this->ProjectileSystem);
}
