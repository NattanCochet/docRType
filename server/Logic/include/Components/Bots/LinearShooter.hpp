/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** LinearShooter
*/

#ifndef LINEARSHOOTER_HPP_
#define LINEARSHOOTER_HPP_

#include "../ABot.hpp"

/**
 * @class LinearShooter
 * @brief A class representing a linear shooter bot.
 *
 * This class inherits from `ABot` and represents a specific type of bot that shoots
 * in a linear direction, either horizontally or vertically, based on the given parameters.
 * It includes functionality to specify the direction of shooting (horizontal or vertical)
 * and the delay between shots.
 */
class LinearShooter : public ABot {
    public:
        /**
         * @brief Constructs a LinearShooter with a specified delay, direction, and vertical speed.
         *
         * @param delay The delay between shots, in seconds (default: 2.0f).
         * @param horizontal If true, the bot shoots horizontally; otherwise, it shoots vertically (default: false).
         * @param vSpeed The vertical speed of the bot (default: 0).
         */
        LinearShooter(float delay = 2.0f, bool horizontal = false, int vSpeed = 0);

        /**
         * @brief Moves the bot within the game world.
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
        bool _honrizontal; /**< Boolean indicating whether the bot shoots horizontally or vertically. */
        int _vSpeed; /**< Vertical speed of the bot. */
};

#endif /* !LINEARSHOOTER_HPP_ */
