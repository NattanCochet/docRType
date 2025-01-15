/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** TpShooter
*/

/**
 * @file TpShooter.hpp
 * @brief Definition of the TpShooter class.
 */

#ifndef TPSHOOTER_HPP_
#define TPSHOOTER_HPP_

#include "../ABot.hpp"
#include "../../MyClock.hpp"
#include "../../ECS/CreateEntity.hpp"
#include <random>
#include <iostream>

/**
 * @class TpShooter
 * @brief A teleporting shooter bot with timed projectile shooting.
 *
 * The TpShooter bot combines teleportation and projectile attacks, using
 * customizable shooting patterns and timing mechanisms.
 */
class TpShooter : public ABot {
    public:
        /**
         * @brief Constructs a TpShooter with specified delay and number of shots.
         *
         * @param delay The delay between teleportation and shots, in seconds.
         * @param nbrShoot The total number of projectiles the bot can shoot.
         */
        TpShooter(float delay, std::size_t nbrShoot);

        /**
         * @brief Destructor for TpShooter.
         */
        ~TpShooter();

        /**
         * @brief Moves the bot within the game world, implementing teleportation logic.
         * @param world Reference to the game world.
         * @param myIndexEntity Index of this entity in the world.
         */
        void moveBot(World &world, std::size_t myIndexEntity) override;

        /**
         * @brief Shoots projectiles from the bot in the game world.
         * @param world Reference to the game world.
         * @param myIndexEntity Index of this entity in the world.
         */
        void shootProjectile(World &world, std::size_t myIndexEntity) override;

    private:
        MyClock _clockShoot;       /**< Clock for managing shooting delays. */
        MyClock _clockWaitShoot;   /**< Clock for managing waiting time before shooting. */
        bool _isShooting;          /**< Flag to indicate if the bot is currently shooting. */
        std::size_t _nbrShootTotal; /**< Total number of projectiles the bot can shoot. */
        std::size_t _nbrShoot;      /**< Remaining projectiles the bot can shoot. */
};

#endif /* !TPSHOOTER_HPP_ */
