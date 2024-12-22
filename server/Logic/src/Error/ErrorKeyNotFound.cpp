/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ErrorKeyNotFound
*/

#include "../../include/Error/ErrorKeyNotFound.hpp"

ErrorKeyNotFound::ErrorKeyNotFound(std::string key, std::string whereError)
    : AError("Key: \"" + key + "\" not found in Map situated in: \"" + whereError + "\"")
{
}
