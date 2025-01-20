/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Bonus
*/

#ifndef BONUS_HPP_
#define BONUS_HPP_
#include "../ECS/World.hpp"
#include "ABonus.hpp"
#include <iostream>
#include <memory>

class Bonus
{
  public:
    Bonus(int id, std::shared_ptr<ABonus> bonus);
    ~Bonus();

    /**
     * @brief Gets the ID of the enemy.
     *
     * @return The ID of the enemy.
     */
    int getId();

    /**
     * @brief Sets the ID of the enemy.
     *
     * @param newId The new ID to set for the enemy.
     */
    void setId(int newId);

    /**
     * @brief Gets the bot associated with the enemy.
     *
     * @return A shared pointer to the bonus.
     */
    std::shared_ptr<ABonus> &getBonus();

    /**
     * @brief Sets the bot for the enemy.
     *
     * @param newBonus A shared pointer to the new bonus to associate with the player.
     */
    void setBonus(std::shared_ptr<ABonus> newBonus);

  private:
    int _id;                        /**< The unique identifier for the enemy */
    std::shared_ptr<ABonus> _bonus; /**< Shared pointer to the bot controlling the enemy's behavior */
};

#endif /* !BONUS_HPP_ */
