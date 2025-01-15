/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ErrorNoObject
*/

#include "../../include/Error/ErrorNoObject.hpp"

ErrorNoObject::ErrorNoObject(std::string objet, std::string where)
    : AError("Error: Object \"" + objet + "\" has no element in it in function -> \"" + where + "\"")
{
}
