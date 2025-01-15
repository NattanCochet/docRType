/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris [WSL: Ubuntu-22.04]
** File description:
** KamikazeShooter
*/

/**
 * @file KamikazeShooter.hpp
 * @brief Definition of the KamikazeShooter class.
 */

#ifndef KAMIKAZESHOOTER_HPP_
#define KAMIKAZESHOOTER_HPP_

#include "../ABot.hpp"

/**
 * @class KamikazeShooter
 * @brief Represents a kamikaze-type bot that can shoot projectiles and deal damage upon collision.
 */
class KamikazeShooter : public ABot {
    public:
        /**
         * @brief Constructor for KamikazeShooter.
         * @param delay Time between actions, defaults to 4.0f.
         * @param vSpeed Vertical speed of the bot, defaults to 5.0f.
         * @param damage Damage dealt by the bot upon collision, defaults to 80.
         */
        KamikazeShooter(float delay = 4.0f, float vSpeed = 5.0f, int damage = 80);

        /**
         * @brief Destructor for KamikazeShooter.
         */
        ~KamikazeShooter();

        /**
         * @brief Sets the vertical speed of the bot.
         * @param newVSpeed The new vertical speed value.
         */
        void setVSpeed(float newVSpeed);

        /**
         * @brief Gets the current vertical speed of the bot.
         * @return The current vertical speed.
         */
        float getVSpeed(void);

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
        float _vSpeed; /**< Vertical speed of the bot. */
        int _damage;   /**< Damage dealt by the bot upon collision. */
};

#endif /* !KAMIKAZESHOOTER_HPP_ */
