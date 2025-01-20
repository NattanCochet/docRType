/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** BigShip
*/

/**
 * @file BigShip.hpp
 * @brief Definition of the BigShip class.
 */

#ifndef BigShip_HPP_
#define BigShip_HPP_

#include "../ABot.hpp"

/**
 * @class BigShip
 * @brief Represents a large ship bot in the game, inheriting from ABot.
 */
class BigShip : public ABot
{
  public:
    /**
     * @brief Constructor for BigShip.
     * @param delay Time between standard actions (e.g., firing projectiles).
     * @param delay2 Delay for special back lasers, defaults to 3.0f.
     * @param delay3 Delay for big laser actions, defaults to 0.6f.
     */
    BigShip(float delay, float delay2 = 3.0f, float delay3 = 0.6f);

    /**
     * @brief Destructor for BigShip.
     */
    ~BigShip();

    /**
     * @brief Shoots projectiles in the game world.
     * @param world Reference to the game world.
     * @param myIndexEntity Index of this entity in the world.
     */
    void shootProjectile(World &world, std::size_t myIndexEntity) override;

    /**
     * @brief Moves the bot within the game world.
     * @param world Reference to the game world.
     * @param myIndexEntity Index of this entity in the world.
     */
    void moveBot(World &world, std::size_t myIndexEntity) override;

  private:
    sf::Clock _bigLaserClock;   /**< Clock to manage big laser timing. */
    sf::Clock _backLasersClock; /**< Clock to manage back laser timing. */
    float _delay2;              /**< Delay between back laser actions. */
    float _delay3;              /**< Delay between big laser actions. */
    bool _isOnScreen;           /**< Is the boss on screen */
};

#endif /* !BigShip_HPP_ */
