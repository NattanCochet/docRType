/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ErrorKeyAlreadyExistInMap
*/

#include "../../include/Error/ErrorKeyAlreadyExistInMap.hpp"

ErrorKeyAlreadyExistInMap::ErrorKeyAlreadyExistInMap(std::string key, std::string whereError)
    : AError("Error: Key " + key + " already exist in map in " + whereError)
{
}
