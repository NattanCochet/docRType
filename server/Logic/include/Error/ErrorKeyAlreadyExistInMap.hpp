/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ErrorKeyAlreadyExistInMap
*/

#ifndef ERRORKEYALREADYEXISTINMAP_HPP_
#define ERRORKEYALREADYEXISTINMAP_HPP_
#include "AError.hpp"

/**
 * @class ErrorKeyAlreadyExistInMap
 * @brief Represents an error when a key already exists in a map.
 * 
 * This error is thrown when an attempt is made to insert a duplicate key
 * into a map. It is derived from the base class `AError` to handle specific
 * error scenarios related to map key uniqueness.
 */
class ErrorKeyAlreadyExistInMap : public AError
{
    public:
        /**
         * @brief Constructor for ErrorKeyAlreadyExistInMap.
         * 
         * Initializes the error with the specific key and the location of the error.
         * 
         * @param key The key that already exists in the map.
         * @param whereError The location or context where the error occurred.
         */
        ErrorKeyAlreadyExistInMap(std::string key, std::string whereError);

        /**
         * @brief Default destructor for ErrorKeyAlreadyExistInMap.
         */
        ~ErrorKeyAlreadyExistInMap() = default;
};

#endif /* !ERRORKEYALREADYEXISTINMAP_HPP_ */
