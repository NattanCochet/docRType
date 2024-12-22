/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ErrorKeyNotFound
*/

#ifndef ERRORKEYNOTFOUND_HPP_
#define ERRORKEYNOTFOUND_HPP_

#include "AError.hpp"

/**
 * @class ErrorKeyNotFound
 * @brief Exception class for handling errors when a key is not found.
 *
 * This class extends the base error class `AError` and is used to signal that a requested key
 * could not be found in a map or a dictionary-like structure.
 */
class ErrorKeyNotFound : public AError
{
    public:
        /**
         * @brief Constructs an ErrorKeyNotFound exception with specific key and location information.
         *
         * This constructor initializes the exception with the key that was not found and
         * the location where the error occurred, providing more context to the error.
         *
         * @param key The key that could not be found.
         * @param whereError A string describing where the error occurred (e.g., the function or file).
         */
        ErrorKeyNotFound(std::string key, std::string whereError);

        /**
         * @brief Destructor for the ErrorKeyNotFound exception.
         *
         * The destructor ensures that any necessary cleanup for the exception object is performed.
         */
        ~ErrorKeyNotFound() = default;
};

#endif /* !ERRORKEYNOTFOUND_HPP_ */
