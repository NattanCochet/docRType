/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ErrorWorldFull
*/

#ifndef ERRORWORLDFULL_HPP_
#define ERRORWORLDFULL_HPP_

#include "AError.hpp"

/**
 * @class ErrorWorldFull
 * @brief Exception class for handling the "world full" error.
 *
 * This class extends the base error class `AError` and is used to signal when the world
 * (or game environment) has reached its maximum number of clients and can no longer accommodate
 * additional users.
 */
class ErrorWorldFull : public AError
{
    public:
        /**
         * @brief Constructs an ErrorWorldFull exception with an optional maximum client number.
         *
         * This constructor initializes the exception with the maximum number of clients allowed
         * in the world. If no value is provided, it defaults to 0, indicating no limit.
         *
         * @param nbrClientMax The maximum number of clients allowed in the world (default is 0).
         */
        ErrorWorldFull(std::size_t nbrClientMax = 0);

        /**
         * @brief Destructor for the ErrorWorldFull exception.
         *
         * The destructor ensures that any necessary cleanup for the exception object is performed.
         */
        ~ErrorWorldFull() = default;
};

#endif /* !ERRORWORLDFULL_HPP_ */
