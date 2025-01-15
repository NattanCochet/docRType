/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** SinusShooter
*/

/**
 * @file SinusShooter.hpp
 * @brief Definition of the SinusoidalShooter class.
 */

#ifndef SINUSSHOOTER_HPP_
#define SINUSSHOOTER_HPP_

#include "../ABot.hpp"

/**
 * @class SinusoidalShooter
 * @brief A bot that moves and shoots projectiles in a sinusoidal pattern.
 *
 * The SinusoidalShooter bot combines sinusoidal movement with projectile shooting,
 * characterized by amplitude, frequency, and vertical speed parameters.
 */
class SinusoidalShooter : public ABot {
    public:
        /**
         * @brief Constructs a SinusoidalShooter with specified parameters.
         *
         * @param delay The delay between each shot, in seconds.
         * @param amplitude The amplitude of the sinusoidal motion.
         * @param frequency The frequency of the sinusoidal motion.
         * @param vSpeed The vertical speed of the bot.
         */
        SinusoidalShooter(float delay, float amplitude, float frequency, float vSpeed);

        /**
         * @brief Moves the bot within the game world following a sinusoidal pattern.
         * @param world Reference to the game world.
         * @param myIndexEntity Index of this entity in the world.
         */
        void moveBot(World &world, std::size_t myIndexEntity) override;

        /**
         * @brief Shoots a projectile in the game world.
         * @param world Reference to the game world.
         * @param myIndexEntity Index of this entity in the world.
         */
        void shootProjectile(World &world, std::size_t myIndexEntity) override;

    private:
        float _amplitude; /**< The amplitude of the sinusoidal movement. */
        float _frequency; /**< The frequency of the sinusoidal movement. */
        float _phase;     /**< The phase offset for the sinusoidal movement. */
        float _vSpeed;    /**< The vertical speed of the bot. */
};

#endif /* !SINUSSHOOTER_HPP_ */
