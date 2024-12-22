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
        float _loadingTime; ///< The time it takes for the projectile to load.
        bool _isRebound; ///< Whether the projectile can rebound.
        bool _canHoldCharging; ///< Whether the projectile can hold charging.
        float _reductionDamage; ///< The amount of damage reduction applied to the projectile.
        float _damageFallOff; ///< The amount of damage fall-off over distance or time.
        int _stack; ///< The stack count for the projectile (if applicable).

    public:
        /**
         * @brief Constructs a new Projectile object with specified properties.
         *
         * @param _damage The initial damage of the projectile.
         * @param _loadingTime The initial loading time for the projectile.
         * @param _isRebound Whether the projectile can rebound.
         * @param _canHoldCharging Whether the projectile can hold charging.
         * @param _reductionDamage The initial damage reduction applied to the projectile.
         * @param _damageFallOff The initial damage fall-off of the projectile.
         */
        Projectile(
            float _damage, float _loadingTime, bool _isRebound,
            bool _canHoldCharging, float _reductionDamage, float _damageFallOff
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
         * @brief Sets the loading time for the projectile.
         *
         * @param newLoadTime The new loading time value.
         */
        void setLoadingTime(float newLoadTime);

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
         * @brief Sets the damage reduction applied to the projectile.
         *
         * @param newDmgReduction The new damage reduction value.
         */
        void setReductionDamage(float newDmgReduction);

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
         * @brief Gets the damage dealt by the projectile.
         *
         * @return The damage value of the projectile.
         */
        float getDamage(void);

        /**
         * @brief Gets the loading time of the projectile.
         *
         * @return The loading time value of the projectile.
         */
        float getLoadingTime(void);

        /**
         * @brief Gets the damage reduction applied to the projectile.
         *
         * @return The damage reduction value.
         */
        float getReductionDmg(void);

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
         * @brief Gets the stack count of the projectile.
         *
         * @return The stack count of the projectile.
         */
        int getStack(void);
};

#endif /* !APROJECTILE_HPP_ */
