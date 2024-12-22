/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Entity
*/

#pragma once
#ifndef ENTITY_HPP_
#define ENTITY_HPP_
#include <iostream>

/**
 * @class Entity
 * @brief Represents a basic entity with a unique identifier.
 *
 * The Entity class provides a way to represent an entity with a unique ID. The ID is used to track and manage
 * entities in a system, such as in a game or an entity-component system (ECS).
 */
class Entity
{
    public:
        /**
         * @brief Constructs an Entity with a specific ID.
         *
         * This constructor initializes the entity with a given unique identifier.
         *
         * @param entity_id The unique ID for the entity.
         */
        explicit Entity(std::size_t entity_id) : id(entity_id) {}

        /**
         * @brief Allows the Entity object to be implicitly converted to its ID.
         *
         * This operator provides a way to use the Entity object directly as its unique ID (std::size_t).
         *
         * @return The unique ID of the entity.
         */
        operator std::size_t() const;

    private:
        /**
         * @brief The unique identifier for the entity.
         *
         * This private member stores the unique ID assigned to the entity.
         */
        std::size_t id;

    friend class registry; ///< Allows the registry class to access the private members of Entity
};

#endif /* !ENTITY_HPP_ */
