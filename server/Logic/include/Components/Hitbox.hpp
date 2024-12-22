/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Hitbox
*/

#pragma once
#ifndef HITBOX_HPP_
#define HITBOX_HPP_
#include "../Vector.hpp"
#include "../Error/ErrorKeyNotFound.hpp"
#include <map>

/**
 * @class Hitbox
 * @brief A class representing a hitbox for collision detection.
 *
 * This class defines a hitbox, which can be either a rectangle or a circle. It stores
 * the position, size, rotation, and collision information, and provides methods to
 * check for collisions and manage collision data.
 */
class Hitbox {
    public:
        /**
         * @enum TYPE
         * @brief Represents the possible types of hitboxes.
         */
        enum TYPE {
            RECTANGLE = 0, ///< A rectangular hitbox.
            CIRCULAR = 1   ///< A circular hitbox.
        };

        /**
         * @enum DIRECTION
         * @brief Represents the possible directions for collision detection.
         */
        enum DIRECTION {
            UP = 0,          ///< Collision from the upward direction.
            UP_RIGHT = 1,    ///< Collision from the upward-right direction.
            RIGHT = 2,       ///< Collision from the right direction.
            DOWN_RIGHT = 3,  ///< Collision from the downward-right direction.
            DOWN = 4,        ///< Collision from the downward direction.
            DOWN_LEFT = 5,   ///< Collision from the downward-left direction.
            LEFT = 6,        ///< Collision from the left direction.
            UP_LEFT = 7      ///< Collision from the upward-left direction.
        };

        /**
         * @brief Constructs a Hitbox with a specified type, position, size, and rotation.
         *
         * @param type The type of the hitbox (RECTANGLE or CIRCULAR).
         * @param position The position of the hitbox.
         * @param size The size (dimensions) of the hitbox.
         * @param rotation The rotation of the hitbox (optional, default is 0.0f).
         */
        Hitbox(TYPE type, Vector<int, 2> position, Vector<int, 2> size, float rotation = 0.0f);

        /**
         * @brief Default constructor for a Hitbox.
         *
         * Initializes the hitbox with default values.
         */
        Hitbox();

        /**
         * @brief Destructor for the Hitbox class.
         *
         * Cleans up any resources used by the hitbox.
         */
        ~Hitbox();

        /**
         * @brief Gets the type of the hitbox.
         *
         * @return The type of the hitbox (RECTANGLE or CIRCULAR).
         */
        TYPE getType() const;

        /**
         * @brief Gets the position of the hitbox.
         *
         * @return The position of the hitbox as a Vector.
         */
        Vector<int, 2> getPosition() const;

        /**
         * @brief Gets the size of the hitbox.
         *
         * @return The size (dimensions) of the hitbox as a Vector.
         */
        Vector<int, 2> getSize() const;

        /**
         * @brief Gets the collision information for a specific ID.
         *
         * This method returns the collision status for each of the 8 directions
         * for a given ID. The result is stored as an array of 8 booleans.
         *
         * @param id The ID for which to retrieve the collision data.
         * @return An array of 8 booleans representing the collision data for the specified ID.
         */
        std::array<bool, 8> getEightAngleCollisionByID(std::size_t id);

        /**
         * @brief Gets the rotation of the hitbox.
         *
         * @return The rotation of the hitbox in degrees.
         */
        float getRotation() const;

        /**
         * @brief Sets the type of the hitbox.
         *
         * @param newType The new type to set (RECTANGLE or CIRCULAR).
         */
        void setType(TYPE newType);

        /**
         * @brief Sets the position of the hitbox.
         *
         * @param newPosition The new position to set as a Vector.
         */
        void setPosition(Vector<int, 2> newPosition);

        /**
         * @brief Sets the position of the hitbox with integer coordinates.
         *
         * @param newXPosition The new X-coordinate to set.
         * @param newYPosition The new Y-coordinate to set.
         */
        void setPosition(int newXPosition, int newYPosition);

        /**
         * @brief Sets the size of the hitbox.
         *
         * @param newSize The new size (dimensions) to set as a Vector.
         */
        void setSize(Vector<int, 2> newSize);

        /**
         * @brief Sets the size of the hitbox with integer dimensions.
         *
         * @param newXSize The new X-dimension to set.
         * @param newYSize The new Y-dimension to set.
         */
        void setSize(int newXSize, int newYSize);

        /**
         * @brief Sets the rotation of the hitbox.
         *
         * @param newRotation The new rotation to set in degrees.
         */
        void setRotation(float newRotation);

        /**
         * @brief Adds collision data for a specific ID.
         *
         * This method adds collision information (an array of booleans for each direction)
         * for a specific ID. The collision data is stored for future checks.
         *
         * @param id The ID to associate with the collision data.
         * @param collisionData The collision data to store for the specified ID.
         */
        void addCollisionWithID(std::size_t id, std::array<bool, 8> collisionData);

        /**
         * @brief Checks if there is a collision for a specific ID.
         *
         * This method checks if there is any collision data associated with the given ID.
         *
         * @param id The ID to check for collision data.
         * @return True if there is a collision with the specified ID, false otherwise.
         */
        bool isCollisionWithID(std::size_t id);

        /**
         * @brief Checks if the hitbox is in a collision state.
         *
         * This method checks if the hitbox has any collision detected.
         *
         * @return True if there is any collision, false otherwise.
         */
        bool isCollision() const;

        /**
         * @brief Checks if the hitbox is colliding in a specific direction.
         *
         * This method checks if the hitbox is colliding in a specific direction.
         *
         * @param direction The direction to check for collision.
         * @return True if the hitbox is colliding in the specified direction, false otherwise.
         */
        bool isCollisionInDirection(DIRECTION direction) const;

        /**
         * @brief Checks if the hitbox is colliding with a specific ID in a specific direction.
         *
         * This method checks if the hitbox has a collision with a specific ID in a specific direction.
         *
         * @param id The ID to check for collision.
         * @param direction The direction to check for collision.
         * @return True if there is a collision with the specified ID and direction, false otherwise.
         */
        bool isCollisionWithIDInDirection(std::size_t id, DIRECTION direction);

    private:
        TYPE _type; ///< The type of the hitbox (RECTANGLE or CIRCULAR).
        Vector<int, 2> _position; ///< The position of the hitbox.
        Vector<int, 2> _size; ///< The size (dimensions) of the hitbox.
        std::map<std::size_t, std::array<bool, 8>> _eightAnglesCollisionByID; ///< A map to store collision data by ID.
        float _rotation; ///< The rotation of the hitbox.
};

#endif /* !HITBOX_HPP_ */
