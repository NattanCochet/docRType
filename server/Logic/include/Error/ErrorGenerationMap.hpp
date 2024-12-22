/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ErrorGenerationMap
*/

#ifndef ERRORGENERATIONMAP_HPP_
#define ERRORGENERATIONMAP_HPP_

#include "AError.hpp"

/**
 * @class ErrorGenerationMap
 * @brief Exception class for handling errors during map generation.
 *
 * This class extends the base error class `AError` and is used to signal that an error occurred
 * during the map generation process, such as an invalid or corrupted map.
 */
class ErrorGenerationMap : public AError
{
    public:
        /**
         * @brief Constructs an ErrorGenerationMap exception with a specific error message.
         *
         * This constructor initializes the exception with an error message that provides more details
         * about the map generation failure.
         *
         * @param error A string describing the error encountered during map generation.
         */
        ErrorGenerationMap(std::string error);

        /**
         * @brief Destructor for the ErrorGenerationMap exception.
         *
         * The destructor ensures that any necessary cleanup for the exception object is performed.
         */
        ~ErrorGenerationMap() = default;

    protected:
    private:
};

#endif /* !ERRORGENERATIONMAP_HPP_ */
