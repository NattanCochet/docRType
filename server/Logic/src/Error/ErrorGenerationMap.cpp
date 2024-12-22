/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ErrorGenerationMap
*/

#include "../../include/Error/ErrorGenerationMap.hpp"

ErrorGenerationMap::ErrorGenerationMap(std::string error)
    : AError("Error in Generation Map: " + error)
{
}
