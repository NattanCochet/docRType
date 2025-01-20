/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Error
*/

/**
 * @file Error.hpp
 * @brief Header file for the Error class, which defines custom error types for the application.
 *
 * The Error class extends std::exception and is used to handle various error conditions in the game,
 * such as issues with fonts, sprites, and missing arguments.
 */

#ifndef ERROR_HPP_
#define ERROR_HPP_
#include <exception>

class Error : public std::exception
{
  public:
    /**
     * @brief Enumeration for different error types in the application.
     *
     * These errors are thrown when specific conditions are met, such as missing files or invalid arguments.
     */
    enum MISTAKE {
        FONT_ERROR,          /**< Error when a font cannot be loaded. */
        SPRITE_ERROR,        /**< Error when a sprite cannot be loaded. */
        SPRITE_NOT_FOUND,    /**< Error when a sprite is not found. */
        TEXT_NOT_FOUND,      /**< Error when a text resource is not found. */
        RECTANGLE_NOT_FOUND, /**< Error when a rectangle shape is not found. */
        BAD_CONSTRUCTOR,     /**< Error when a constructor is used incorrectly. */
        MISSING_ARGUMENTS,   /**< Error when arguments are missing in a function or constructor. */
        ERROR_IN_RECEIVE_MESSAGE
    };

  public:
    /**
     * @brief Constructor for the Error class.
     *
     * Initializes the error with the specified error type.
     *
     * @param error The error type to be thrown.
     */
    Error(MISTAKE error) noexcept;

    /**
     * @brief Destructor for the Error class.
     *
     * The destructor does not perform any special actions.
     */
    ~Error() noexcept
    {
    }

    /**
     * @brief Returns a C-style string that describes the error.
     *
     * This function overrides std::exception::what and provides a custom error message
     * based on the error type.
     *
     * @return A C-style string that describes the error.
     */
    const char *what() noexcept;

  private:
    MISTAKE _error; /**< The specific error type that this object represents. */
};

#endif /* !ERROR_HPP_ */
