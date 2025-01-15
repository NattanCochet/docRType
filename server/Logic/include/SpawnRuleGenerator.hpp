/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** SpawnRuleGenerator
*/

#ifndef SPAWNRULEGENERATOR_HPP_
#define SPAWNRULEGENERATOR_HPP_

#include <list>
#include <iostream>
#include <functional>
#include "Error/ErrorKeyNotFound.hpp"

/**
 * @namespace RuleGenerator
 * @brief The namespace to generate mob the world
 */
namespace SpawnRule {
    /**
     * @class EntityType
     * @brief Structure representing an entity type with its spawning characteristics.
     */
    class EntityType {
        public:
            std::size_t id;             ///< Unique identifier for the entity.
            float baseThreshold;        ///< Base threshold for spawning (-1 to 1).
            float levelScaling;         ///< Scaling factor per level.
            float maxThresholdBonus;    ///< Maximum bonus to the threshold.
            std::size_t minLevel;       ///< Minimum level required for spawning.
            std::size_t sizeEntity;     ///< Size of the entity to spawn.
            int scoreByDeath;           ///< Award score to the player when this entity dies.
    };

    /**
     * @class Generator
     * @brief Class for generating spawn rules for entities.
     */
    class Generator {
        public:
            /**
             * @enum ENTITIES
             * @brief Enumeration of supported entity types.
             */
            enum ENTITIES {
                NOTHING = 0,   ///< No entity.
                DECOR = 1,  ///< Decoration entity.
                LINEAR_SHOOTER_VERTICAL = 2, ///< First type of enemy.
                LINEAR_SHOOTER_HORIZONTAL = 3,  ///< Second type of enemy.
                TP_SHOOTER = 4  ///< Third type of enemy.
            };

        public:
            /**
             * @brief Constructor for the SpawnRuleGenerator class.
             */
            Generator();

            /**
             * @brief Destructor for the SpawnRuleGenerator class.
             */
            ~Generator();

            /**
             * @brief Adds an entity to the list of available entities.
             *
             * @param newEntity Reference to an EntityType object.
             */
            void addEntity(const EntityType &newEntity);

            /**
             * @brief Adds an entity to the list of available entities with explicit parameters.
             *
             * @param id Unique identifier for the entity.
             * @param baseThreshold Base threshold for spawning (-1 to 1).
             * @param levelScaling Scaling factor per level.
             * @param maxThresholdBonus Maximum bonus to the threshold.
             * @param sizeEntity The size square of the entity which allow it to spawn.
             * @param scoreByDeath The score awards to the player who kill this entity.
             * @param minLevel Minimum level required for spawning (default value: 0).
             */
            void addEntity(std::size_t id, float baseThreshold, float levelScaling,
                float maxThresholdBonus, std::size_t sizeEntity, int scoreByDeath = 0, std::size_t minLevel = 0);

            /**
             * @brief Creates a spawn rule function based on the ENTITIES enumeration.
             *
             * @param level Current level used to generate the rule.
             * @return A function that takes a float parameter and returns an ENTITIES type.
             */
            std::function<ENTITIES(float)> createFunctionForRuleWithEnum(const std::size_t &level);

            /**
             * @brief Creates a spawn rule function based on entity IDs.
             *
             * @param level Current level used to generate the rule.
             * @return A function that takes a float parameter and returns an entity ID (int).
             */
            std::function<int(float)> createFunctionForRuleWithID(const std::size_t &level);

            /**
             * @brief Get Entity where the id which match whit entity ID
             *
             * @return The struct EntityType which match with the ID
             */
            SpawnRule::EntityType &getEntity(std::size_t id);

            /**
             * @brief Get the size of the entity which match whit entity ID
             *
             * @return The size of the entity id
             */
            std::size_t getSizeEntity(std::size_t id);

            /**
             * @brief Check if have enought place to spawn an entity depend on its size
             *
             * @param world The vector of vector of int, generated with the class GenerateWorld
             * @param y The y-axis, represente the beginning of the y-axis
             * @param x The x-axis, represente the beginning of the x-axis
             * @param sizeEntity The size of the entity to spawn (square)
             *
             * @return If it's possible to spawn the entity in the current location (y, x) and the size.
             *         If is's True the square is fill in by 0 (entity VOID)
             */
            bool hasEnoughtPlaceForEnemy(std::vector<std::vector<int>> &world, std::size_t y, std::size_t x, std::size_t sizeEntity);

        private:
            std::list<EntityType> _entities; ///< List of entities available for spawn rules.
    };
};

#endif /* !SPAWNRULEGENERATOR_HPP_ */
