/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ErrorVector
*/

#include "../../include/Error/ErrorVector.hpp"

ErrorVector::ErrorVector(std::string errorVector)
    : AError("Error in vector: " + errorVector)
{
}
