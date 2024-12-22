/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ErrorWorldFull
*/

#include "../../include/Error/ErrorWorldFull.hpp"

ErrorWorldFull::ErrorWorldFull(std::size_t nbrClientMax)
    : AError("Error with number of client in world >= " + std::to_string(nbrClientMax))
{
}
