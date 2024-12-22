/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** LinearShooter
*/

#include "../ABot.hpp"

#ifndef LINEARSHOOTER_HPP_
#define LINEARSHOOTER_HPP_

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
         * @brief Constructs a LinearShooter with a specified delay.
         *
         * @param delay The delay between shots, in seconds.
         */
        LinearShooter(float delay);

        /**
         * @brief Constructs a LinearShooter with a specified delay and direction.
         *
         * @param delay The delay between shots, in seconds.
         * @param horizontal If true, the bot shoots horizontally; otherwise, it shoots vertically.
         */
        LinearShooter(float delay, bool horizontal);

        /**
         * @brief Default constructor for LinearShooter.
         *
         * Initializes the bot with default values for delay and direction (horizontal).
         */
        LinearShooter();

        /**
         * @brief Checks if the LinearShooter shoots horizontally.
         *
         * @return True if the bot shoots horizontally, false if it shoots vertically.
         */
        bool isHonrizontal();

    private:
        bool _honrizontal; ///< Boolean indicating whether the bot shoots horizontally or not.
};

#endif /* !LINEARSHOOTER_HPP_ */
