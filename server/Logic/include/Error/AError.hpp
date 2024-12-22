/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** AError
*/

#ifndef AERROR_HPP_
#define AERROR_HPP_
#include <iostream>
#include <string>

/**
 * @class AError
 * @brief Custom exception class for handling errors.
 *
 * This class extends the standard exception class and allows for custom error messages.
 */
class AError : public std::exception
{
    public:
        /**
         * @brief Constructor for AError.
         * @param error The error message to store.
         */
        explicit AError(const std::string& error): _what(error) {}

        /**
         * @brief Destructor for AError.
         */
        virtual ~AError() noexcept = default;

        /**
         * @brief Returns the error message.
         *
         * Overrides the `what()` method of the std::exception class to return the error message.
         * @return The error message stored in the object.
         */
        const char* what() const noexcept override
        {
            return (_what.c_str());
        }

    protected:
        /**
         * @brief The error message.
         *
         * This string holds the error message that will be returned when the exception is thrown.
         */
        std::string _what;
};

#endif /* !AERROR_HPP_ */
