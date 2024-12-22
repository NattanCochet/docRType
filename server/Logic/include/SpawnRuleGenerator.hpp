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

/**
 * @struct EntityType
 * @brief Structure representing an entity type with its spawning characteristics.
 */
struct EntityType {
    std::size_t id;             ///< Unique identifier for the entity.
    float baseThreshold;        ///< Base threshold for spawning (-1 to 1).
    float levelScaling;         ///< Scaling factor per level.
    float maxThresholdBonus;    ///< Maximum bonus to the threshold.
    std::size_t minLevel;       ///< Minimum level required for spawning.
};

/**
 * @class SpawnRuleGenerator
 * @brief Class for generating spawn rules for entities.
 */
class SpawnRuleGenerator {
    public:
        /**
         * @enum ENTITIES
         * @brief Enumeration of supported entity types.
         */
        enum ENTITIES {
            NOTHING = 0,   ///< No entity.
            DECOR = 1,  ///< Decoration entity.
            ENEMY1 = 2, ///< First type of enemy.
            ENEMY2 = 3  ///< Second type of enemy.
        };

    public:
        /**
         * @brief Constructor for the SpawnRuleGenerator class.
         */
        SpawnRuleGenerator();

        /**
         * @brief Destructor for the SpawnRuleGenerator class.
         */
        ~SpawnRuleGenerator();

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
         * @param minLevel Minimum level required for spawning (default value: 0).
         */
        void addEntity(std::size_t id, float baseThreshold, float levelScaling,
                      float maxThresholdBonus, std::size_t minLevel = 0);

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

    private:
        std::list<EntityType> _entities; ///< List of entities available for spawn rules.
};

#endif /* !SPAWNRULEGENERATOR_HPP_ */