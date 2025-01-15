/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ErrorNoObject
*/

#ifndef ERRORNOOBJECT_HPP_
#define ERRORNOOBJECT_HPP_
#include "AError.hpp"

/**
 * @class ErrorNoObject
 * @brief Represents an error when a specific object is not found.
 * 
 * This error is thrown when an attempt is made to access or manipulate an
 * object that does not exist in the system. It is derived from the base
 * class `AError` to handle this particular error scenario.
 */
class ErrorNoObject : public AError
{
    public:
        /**
         * @brief Constructor for ErrorNoObject.
         * 
         * Initializes the error with the specific object name and the location
         * where the error occurred.
         * 
         * @param objet The name of the object that is missing or not found.
         * @param where The location or context where the error occurred.
         */
        ErrorNoObject(std::string objet, std::string where);

        /**
         * @brief Default destructor for ErrorNoObject.
         */
        ~ErrorNoObject() = default;
};

#endif /* !ERRORNOOBJECT_HPP_ */
