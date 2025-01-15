/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ABot
*/

#include <SFML/System.hpp>
#include "../ECS/World.hpp"
#include "Position.hpp"
#include "Projectile.hpp"
#include "Hitbox.hpp"
#include "Velocity.hpp"

#ifndef ABOT_HPP_
#define ABOT_HPP_

/**
 * @class ABot
 * @brief Abstract base class for a bot in the game.
 *
 * This class manages the bot's delay and clock.
 */
class ABot {
    public:
        /**
         * @brief Destructor for ABot.
         */
        virtual ~ABot() = default;

        /**
         * @brief Gets the delay time for the bot.
         * @return The delay value.
         */
        float getDelay();

        /**
         * @brief Gets the clock used to manage time for the bot.
         * @return A reference to the bot's clock.
         */
        sf::Clock &getClock();

        /**
         * @brief Moves the bot
         */
        virtual void moveBot(World &world, std::size_t myIndexEntity) = 0;

        /**
         * @brief Shoots the bot's projectile
         */
        virtual void shootProjectile(World &world, std::size_t myIndexEntity) = 0;

    protected:
        /**
         * @brief The delay value for the bot.
         *
         * This represents the delay time that the bot will use for various operations.
         */
        float _delay;

        /**
         * @brief The clock used to track time for the bot's actions.
         */
        sf::Clock _clock;

};

#endif /* !ABOT_HPP_ */
