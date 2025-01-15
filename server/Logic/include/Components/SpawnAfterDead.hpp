/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** SpawnAfterDead
*/

#ifndef SPAWNAFTERDEAD_HPP_
#define SPAWNAFTERDEAD_HPP_
#include <iostream>

/**
 * @class SpawnAfterDead
 * @brief Represents an entity that can be spawned after it has died.
 * 
 * This class handles the logic for entities that are marked as "dead" and 
 * can later be respawned, keeping track of their ID before they died.
 */
class SpawnAfterDead {
    public:
        /**
         * @brief Constructor for the SpawnAfterDead class.
         * 
         * Initializes the class with the ID of the entity before it died.
         * 
         * @param idBeforeDead The ID of the entity before it died.
         */
        SpawnAfterDead(std::size_t idBeforeDead);

        /**
         * @brief Destructor for the SpawnAfterDead class.
         * 
         * Cleans up any resources used by the SpawnAfterDead object.
         */
        ~SpawnAfterDead();

        /**
         * @brief Gets the ID of the entity before it died.
         * 
         * @return The ID of the entity before it died.
         */
        const std::size_t &getIdBeforeDead();

        /**
         * @brief Sets the ID of the entity before it died.
         * 
         * @param newID The new ID of the entity before it died.
         */
        void setIdBeforeDead(const std::size_t &newID);

        /**
         * @brief Checks if the entity is dead.
         * 
         * @return True if the entity is dead, false otherwise.
         */
        const bool &getIsDead();

        /**
         * @brief Marks the entity as dead.
         * 
         * This method sets the entity's dead status to true.
         */
        void entityIsDead();

    private:
        std::size_t _idBeforeDead; /**< The ID of the entity before it died */
        bool _isDead; /**< Flag to check if the entity is dead */
};

#endif /* !SPAWNAFTERDEAD_HPP_ */
