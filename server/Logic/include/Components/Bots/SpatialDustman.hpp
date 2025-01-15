/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** SpatialDustman
*/

/**
 * @file SpatialDustman.hpp
 * @brief Definition of the SpatialDustman class.
 */

#ifndef SPATIALDUSTMAN_HPP_
#define SPATIALDUSTMAN_HPP_

#include "../ABot.hpp"

/**
 * @class SpatialDustman
 * @brief A bot that manages multiple shooting patterns across different columns.
 *
 * The SpatialDustman is a specialized bot that divides its attacks across
 * multiple columns, each with its own timing and configuration.
 */
class SpatialDustman : public ABot {
    public:
        /**
         * @brief Constructs a SpatialDustman with specified delays for each column.
         *
         * @param delay General delay for bot actions.
         * @param column1 Delay for column 1 shooting (default: 1.5f).
         * @param column2 Delay for column 2 shooting (default: 2.0f).
         * @param column3 Delay for column 3 shooting (default: 1.3f).
         * @param column4 Delay for column 4 shooting (default: 0.9f).
         */
        SpatialDustman(float delay, float column1 = 1.5f, float column2 = 2.0f, float column3 = 1.3f, float column4 = 0.9f);

        /**
         * @brief Destructor for SpatialDustman.
         */
        ~SpatialDustman();

        /**
         * @brief Shoots projectiles in the game world, managing multiple columns.
         * @param world Reference to the game world.
         * @param myIndexEntity Index of this entity in the world.
         */
        void shootProjectile(World &world, std::size_t myIndexEntity) override;

        /**
         * @brief Handles movement of the bot in the game world.
         * @param world Reference to the game world.
         * @param myIndexEntity Index of this entity in the world.
         */
        void moveBot(World &world, std::size_t myIndexEntity) override {
            return;
        }

    private:
        float _column1; /**< Delay for column 1 shooting. */
        float _column2; /**< Delay for column 2 shooting. */
        float _column3; /**< Delay for column 3 shooting. */
        float _column4; /**< Delay for column 4 shooting. */
        sf::Clock _clock1; /**< Clock for column 1 shooting. */
        sf::Clock _clock2; /**< Clock for column 2 shooting. */
        sf::Clock _clock3; /**< Clock for column 3 shooting. */
        sf::Clock _clock4; /**< Clock for column 4 shooting. */
};

#endif /* !SPATIALDUSTMAN_HPP_ */
