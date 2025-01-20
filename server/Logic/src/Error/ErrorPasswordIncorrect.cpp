/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ErrorPasswordIncorrect
*/

#include "../../include/Error/ErrorPasswordIncorrect.hpp"

ErrorPasswordIncorrect::ErrorPasswordIncorrect(std::string password) :
    AError("Error with password: Not the same password (\"" + password + "\")")
{
}
