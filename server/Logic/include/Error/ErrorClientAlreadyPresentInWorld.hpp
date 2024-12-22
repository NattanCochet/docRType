/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ErrorClientAlreadyPresentInWorld
*/

#ifndef ERRORCLIENTALREADYPRESENTINWORLD_HPP_
#define ERRORCLIENTALREADYPRESENTINWORLD_HPP_
#include "AError.hpp"

/**
 * @class ErrorClientAlreadyPresentInWorld
 * @brief Exception class for handling the case where a client is already present in the world.
 *
 * This class extends the base error class `AError` and is used to signal that a client with a given ID
 * is already present in the world, preventing further actions related to the client.
 */
class ErrorClientAlreadyPresentInWorld : public AError
{
    public:
        /**
         * @brief Constructs an ErrorClientAlreadyPresentInWorld exception with a specific client ID.
         *
         * This constructor initializes the exception with the client ID, allowing the error to be
         * associated with a specific client.
         *
         * @param clientID The ID of the client that is already present in the world.
         */
        ErrorClientAlreadyPresentInWorld(std::size_t clientID);

        /**
         * @brief Destructor for the ErrorClientAlreadyPresentInWorld exception.
         *
         * The destructor ensures that any necessary cleanup for the exception object is performed.
         */
        ~ErrorClientAlreadyPresentInWorld() = default;

    protected:
    private:
};

#endif /* !ERRORCLIENTALREADYPRESENTINWORLD_HPP_ */
