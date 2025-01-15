/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Ennemy
*/

#include <memory>
#include "ABot.hpp"
#include "Bots/LinearShooter.hpp"
#include "Bots/TpShooter.hpp"

#ifndef ENNEMY_HPP_
#define ENNEMY_HPP_

/**
 * @class Ennemy
 * @brief Represents an enemy in the game.
 * 
 * The Ennemy class holds an ID and a pointer to a bot (ABot) that represents the
 * enemy's behavior. The bot could be a specific type of bot such as a LinearShooter
 * or TpShooter, and the ID can be used for unique identification of the enemy.
 */
class Ennemy {
    public:
        /**
         * @brief Constructor for the Ennemy class.
         * 
         * Initializes an Ennemy object with a given ID and a bot (ABot).
         * 
         * @param id The unique identifier for the enemy.
         * @param bot A shared pointer to the bot that defines the enemy's behavior.
         */
        Ennemy(int id, std::shared_ptr<ABot> bot);

        /**
         * @brief Destructor for the Ennemy class.
         * 
         * Cleans up any resources used by the Ennemy object.
         */
        ~Ennemy();

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
         * @return A shared pointer to the bot.
         */
        std::shared_ptr<ABot> getBot();

        /**
         * @brief Sets the bot for the enemy.
         * 
         * @param newBot A shared pointer to the new bot to associate with the enemy.
         */
        void setBot(std::shared_ptr<ABot> newBot);

    private:
        int _id; /**< The unique identifier for the enemy */
        std::shared_ptr<ABot> _bot; /**< Shared pointer to the bot controlling the enemy's behavior */
};

#endif /* !ENNEMY_HPP_ */
