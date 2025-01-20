/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Entity
*/

/**
 * @file Entity.hpp
 * @brief Header file for the Entity class, representing a unique entity in the system.
 *
 * This class provides an entity with a unique ID and enables conversion to a `std::size_t` for easier use in systems
 * like registries or other data structures that require entity identification.
 */

#pragma once
#ifndef ENTITY_HPP_
#define ENTITY_HPP_
#include <iostream>

class Entity
{
  public:
    /**
     * @brief Construct an Entity with a unique ID.
     * @param entity_id The unique identifier for this entity.
     */
    explicit Entity(std::size_t entity_id) : id(entity_id)
    {
    }

    friend class registry; ///< Grant access to the `registry` class.

    std::size_t id; ///< The unique ID of the entity.

    /**
     * @brief Implicit conversion to `std::size_t`.
     *
     * This operator allows the entity to be treated as a `std::size_t` directly.
     * For example, an `Entity` object can be used in containers or comparisons that
     * expect a `std::size_t` value.
     *
     * @return The unique ID of the entity.
     */
    operator std::size_t() const;
};

#endif /* !ENTITY_HPP_ */
