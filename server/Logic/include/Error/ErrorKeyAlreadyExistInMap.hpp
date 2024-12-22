/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ErrorKeyAlreadyExistInMap
*/

#ifndef ERRORKEYALREADYEXISTINMAP_HPP_
#define ERRORKEYALREADYEXISTINMAP_HPP_
#include "AError.hpp"

class ErrorKeyAlreadyExistInMap : public AError
{
    public:
        ErrorKeyAlreadyExistInMap(std::string key, std::string whereError);
        ~ErrorKeyAlreadyExistInMap() = default;
};

#endif /* !ERRORKEYALREADYEXISTINMAP_HPP_ */
