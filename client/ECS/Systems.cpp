/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** LoadSystems
*/

#include "Systems.hpp"

Systems::Systems()
{
}

Systems::~Systems()
{
}

void Systems::loadSystemsInWorld(World &world)
{
    Registry &r = world.getRegistry();
    r.register_systems(this->drawableSystem);
    r.register_systems(this->clickableSystem);
    r.register_systems(this->controllableSystem);
}