/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Error
*/

#include "Error.hpp"

Error::Error(MISTAKE error) noexcept : _error(error)
{
}

const char *Error::what() noexcept
{
    switch (_error) {
    case FONT_ERROR:
        return "Error with a font.";
    case SPRITE_ERROR:
        return "Error with a sprite.";
    case SPRITE_NOT_FOUND:
        return "Error: sprite not found in map.";
    case TEXT_NOT_FOUND:
        return "Error: text not found in map.";
    case RECTANGLE_NOT_FOUND:
        return "Error: rectangle not found in map.";
    case BAD_CONSTRUCTOR:
        return "Using bad constructor.";
    case MISSING_ARGUMENTS:
        return "Missing one or many arguments.";
    case ERROR_IN_RECEIVE_MESSAGE:
        return "Message received contains error.";
    default:
        return "Unknown error.";
    }
}
