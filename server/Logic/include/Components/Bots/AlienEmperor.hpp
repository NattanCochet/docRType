/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris [WSL: Ubuntu-22.04]
** File description:
** AlienEmperor
*/

/**
 * @file AlienEmperor.hpp
 * @brief Definition of the AlienEmperor class.
 */

#ifndef AlienEmperor_HPP_
#define AlienEmperor_HPP_

#include "../ABot.hpp"

/**
 * @class AlienEmperor
 * @brief Represents an advanced bot type in the game, inheriting from ABot.
 */
class AlienEmperor : public ABot {
    public:
        /**
         * @brief Constructor for AlienEmperor.
         * @param delay Time between two actions (e.g., firing projectiles).
         * @param delay2 Default delay for certain actions, defaults to 5.0f.
         */
        AlienEmperor(float delay, float delay2 = 5.0f);

        /**
         * @brief Destructor for AlienEmperor.
         */
        ~AlienEmperor();

        /**
         * @brief Shoots a projectile in the world.
         * @param world Reference to the game world.
         * @param myIndexEntity Index of this entity in the world.
         */
        void shootProjectile(World &world, std::size_t myIndexEntity) override;

        /**
         * @brief Moves the bot within the world.
         * @param world Reference to the game world.
         * @param myIndexEntity Index of this entity in the world.
         */
        void moveBot(World &world, std::size_t myIndexEntity) override
        {
            return;
        }

    private:
        float _delayShip; /**< Delay between ship spawns. */
        sf::Clock _shipSpawn; /**< Clock to manage ship spawning. */
};

#endif /* !AlienEmperor_HPP_ */
