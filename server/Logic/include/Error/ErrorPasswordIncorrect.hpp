/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ErrorPasswordIncorrect
*/

#ifndef ERRORPASSWORDINCORRECT_HPP_
#define ERRORPASSWORDINCORRECT_HPP_

#include "AError.hpp"

/**
 * @class ErrorPasswordIncorrect
 * @brief Exception class for handling incorrect password errors.
 *
 * This class extends the base error class `AError` and is used to signal that an incorrect
 * password was provided during an authentication attempt.
 */
class ErrorPasswordIncorrect : public AError
{
    public:
        /**
         * @brief Constructs an ErrorPasswordIncorrect exception with optional password information.
         *
         * This constructor initializes the exception with the incorrect password, which can be
         * used for debugging purposes. The password can be left empty if not needed.
         *
         * @param password The incorrect password (optional).
         */
        ErrorPasswordIncorrect(std::string password = "");

        /**
         * @brief Destructor for the ErrorPasswordIncorrect exception.
         *
         * The destructor ensures that any necessary cleanup for the exception object is performed.
         */
        ~ErrorPasswordIncorrect() = default;
};

#endif /* !ERRORPASSWORDINCORRECT_HPP_ */
