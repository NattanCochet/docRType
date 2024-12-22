/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ErrorVector
*/

#ifndef ERRORVECTOR_HPP_
#define ERRORVECTOR_HPP_

#include "AError.hpp"

/**
 * @class ErrorVector
 * @brief Exception class for handling errors related to vectors.
 *
 * This class extends the base error class `AError` and is used to signal errors
 * that occur when working with vectors, such as invalid operations or data processing issues.
 */
class ErrorVector : public AError
{
    public:
        /**
         * @brief Constructs an ErrorVector exception with optional error details.
         *
         * This constructor initializes the exception with a string describing the error.
         * The error message can be left empty if no specific message is provided.
         *
         * @param errorVector A string describing the error related to the vector (optional).
         */
        ErrorVector(std::string errorVector = "");

        /**
         * @brief Destructor for the ErrorVector exception.
         *
         * The destructor ensures that any necessary cleanup for the exception object is performed.
         */
        ~ErrorVector() = default;
};

#endif /* !ERRORVECTOR_HPP_ */
