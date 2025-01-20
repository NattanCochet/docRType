/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** AProjectile
*/

#pragma once
#ifndef APROJECTILE_HPP_
#define APROJECTILE_HPP_
#include <iostream>
#include <vector>

/**
 * @class Projectile
 * @brief A class representing a projectile with various properties.
 *
 * This class manages the properties of a projectile, including damage, loading time,
 * rebound behavior, charging capability, damage reduction, and damage fall-off.
 * It provides getter and setter methods for each property.
 */
class Projectile {

    private:
        float _damage; ///< The damage dealt by the projectile.
        bool _isRebound; ///< Whether the projectile can rebound.
        bool _canHoldCharging; ///< Whether the projectile can hold charging.
        float _damageFallOff; ///< The amount of damage fall-off over distance or time.
        std::size_t _entityIDBelong; ///< The ID of the shooter
        int _stack; ///< The stack count for the projectile (if applicable).
        std::vector<std::size_t> _entityIDAlreadyTouch;

    public:
        /**
         * @brief Constructs a new Projectile object with specified properties.
         *
         * @param damage The initial damage of the projectile.
         * @param isRebound Whether the projectile can rebound.
         * @param canHoldCharging Whether the projectile can hold charging.
         * @param damageFallOff The initial damage fall-off of the projectile.
         * @param entityIDBelong The ID of the shooter
         */
        Projectile(
            float damage, bool isRebound, bool canHoldCharging, float damageFallOff,
            std::size_t entityIDBelong
        );

        /**
         * @brief Destructor for the Projectile class.
         */
        ~Projectile();

        /**
         * @brief Sets the damage dealt by the projectile.
         *
         * @param newDmg The new damage value for the projectile.
         */
        void setDamage(float newDmg);

        /**
         * @brief Sets whether the projectile can rebound.
         *
         * @param newRebound True if the projectile can rebound, false otherwise.
         */
        void setIsRebound(bool newRebound);

        /**
         * @brief Sets whether the projectile can hold charging.
         *
         * @param newCharge True if the projectile can hold charging, false otherwise.
         */
        void setHoldCharging(bool newCharge);

        /**
         * @brief Sets the damage fall-off of the projectile.
         *
         * @param newDmgFalloff The new damage fall-off value.
         */
        void setDamageFallOff(float newDmgFalloff);

        /**
         * @brief Sets the stack count of the projectile.
         *
         * @param newStack The new stack count value.
         */
        void setStack(int newStack);

        /**
         * @brief Sets the entity ID belong to this new ID
         *
         * @param newID The new ID to assign
         */
        void setEntityIDBelong(std::size_t newID);
        /**
         * @brief Gets the damage dealt by the projectile.
         *
         * @return The damage value of the projectile.
         */
        float getDamage(void);

        /**
         * @brief Gets the damage fall-off of the projectile.
         *
         * @return The damage fall-off value.
         */
        float getDmgFalloff(void);

        /**
         * @brief Gets whether the projectile can rebound.
         *
         * @return True if the projectile can rebound, false otherwise.
         */
        bool getRebound(void);

        /**
         * @brief Gets whether the projectile can hold charging.
         *
         * @return True if the projectile can hold charging, false otherwise.
         */
        bool getCanHoldCharge(void);

        /**
         * @brief Gets the entity ID belong of this projectile
         *
         * @return The entity ID belong to the projectile
         */
        std::size_t getEntityIDBelong(void);

        /**
         * @brief Gets the stack count of the projectile.
         *
         * @return The stack count of the projectile.
         */
        int getStack(void);

        void addEntityIDAlreadyTouch(const std::size_t &entityID) noexcept;

        const bool isEntityIDAlreadyTouch(const std::size_t &entityID) noexcept;

        void clearEntityIDAlreadyTouch() noexcept;
};

#endif /* !APROJECTILE_HPP_ */
