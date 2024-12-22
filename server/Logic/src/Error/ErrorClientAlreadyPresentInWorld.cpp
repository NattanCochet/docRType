/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ErrorClientAlreadyPresentInWorld
*/

#include "../../include/Error/ErrorClientAlreadyPresentInWorld.hpp"

ErrorClientAlreadyPresentInWorld::ErrorClientAlreadyPresentInWorld(std::size_t clientID)
    : AError("Error: ClientID (" + std::to_string(clientID) + ") already in world")
{
}
