/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Area
*/

/**
 * @file Area.hpp
 * @brief Declaration of the Area class, which defines a circular area in the game world.
 */

#ifndef AREA_HPP_
#define AREA_HPP_

#include "../Vector.hpp"
#include <unordered_set>
#include <algorithm>

/**
 * @class Area
 * @brief Represents a circular area in the game world, used for collision or proximity checks.
 *
 * The Area class provides mechanisms to track entities within a specified radius and check
 * their presence based on an entity's position and ID.
 */
class Area {
    public:
        /**
         * @brief Constructs an Area with a given radius and position.
         * 
         * @param radius The radius of the circular area.
         * @param position The position of the area's center, defaulting to (0, 0).
         */
        Area(float radius, Vector<int, 2> position = Vector<int, 2>(0, 0));

        /**
         * @brief Destructor for the Area class.
         */
        ~Area();

        /**
         * @brief Retrieves the radius of the area.
         * 
         * @return A constant reference to the radius.
         */
        const float &getRadius() const noexcept;

        /**
         * @brief Retrieves the position of the area's center.
         * 
         * @return A reference to the position vector.
         */
        Vector<int, 2> &getPosition() noexcept;

        /**
         * @brief Retrieves the ID of the entity associated with this area.
         * 
         * @return A constant reference to the entity ID.
         */
        const std::size_t &getEntityBelong() const noexcept;

        /**
         * @brief Checks if a given entity ID is within the area.
         * 
         * @param otherEntityID The ID of the entity to check.
         * @return True if the entity is within the area, false otherwise.
         */
        const bool isInAreaOfEntity(const std::size_t &otherEntityID) const noexcept;

        /**
         * @brief Retrieves all entity IDs currently within the area.
         * 
         * @return A constant reference to a set of entity IDs.
         */
        const std::unordered_set<std::size_t> &getAllEntityInArea() const noexcept;

        /**
         * @brief Sets the radius of the area.
         * 
         * @param radius The new radius.
         */
        void setRadius(const float &radius) noexcept;

        /**
         * @brief Sets the position of the area's center.
         * 
         * @param newPosition The new position vector.
         */
        void setPostion(const Vector<int, 2> newPosition) noexcept;

        /**
         * @brief Assigns an entity ID to the area.
         * 
         * @param newEntityIDBelong The new entity ID to associate with the area.
         */
        void setEntityIDBelong(const std::size_t &newEntityIDBelong) noexcept;

        /**
         * @brief Adds an entity ID to the set of entities within the area.
         * 
         * @param entityID The ID of the entity entering the area.
         */
        void anEntityIsEnterArea(const std::size_t entityID) noexcept;

        /**
         * @brief Clears all data associated with the area, including its entity list.
         */
        void clearData() noexcept;

    private:
        float _radius; /**< The radius of the circular area. */
        Vector<int, 2> _position; /**< The position of the area's center. */
        std::unordered_set<std::size_t> _collisionsByID; /**< Set of entity IDs currently within the area. */
        std::size_t _entityIDBelong; /**< The ID of the entity associated with this area. */
};

#endif /* !AREA_HPP_ */
