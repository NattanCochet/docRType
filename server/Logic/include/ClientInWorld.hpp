/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ClientInWorld
*/

#ifndef CLIENTINWORLD_HPP_
#define CLIENTINWORLD_HPP_
#include <iostream>

/**
 * @class ClientInWorld
 * @brief Represents a client within the game world, with properties like
 *        client ID, score, and name.
 * 
 * This class is used to store and manage the client's information such as
 * their unique ID, score during the game, maximum score they have achieved,
 * and their name (defaulting to "Unknown").
 */
class ClientInWorld {
    public:
        /**
         * @brief Default constructor for ClientInWorld.
         * 
         * Initializes the client with default values (ID = 0, score = 0, 
         * max score = -1, name = "Unknown").
         */
        ClientInWorld();

        /**
         * @brief Parametrized constructor for ClientInWorld.
         * 
         * Initializes the client with a specified ID, name, and max score.
         * 
         * @param clientID The unique ID of the client.
         * @param name The name of the client (default is "Unknown").
         * @param maxScore The maximum score for the client (default is -1).
         */
        ClientInWorld(std::size_t clientID, std::string name = "Unknown", int maxScore = -1);

        /**
         * @brief Destructor for ClientInWorld.
         */
        ~ClientInWorld();

    public:
        /**
         * @brief Getter for the client ID.
         * 
         * @return The unique client ID.
         */
        std::size_t getClientID();

        /**
         * @brief Getter for the current score of the client.
         * 
         * @return The client's current score.
         */
        int getScore();

        /**
         * @brief Getter for the client's maximum score.
         * 
         * @return The maximum score the client has achieved.
         */
        int getMaxScore();

        /**
         * @brief Getter for the client's name.
         * 
         * @return The name of the client.
         */
        std::string getName();

    public:
        /**
         * @brief Setter for the client ID.
         * 
         * @param newClientID The new client ID to set.
         */
        void setClientID(std::size_t newClientID);

        /**
         * @brief Setter for the current score of the client.
         * 
         * @param newScore The new score to set.
         */
        void setScore(int newScore);

        /**
         * @brief Adds a specified score to the client's current score.
         * 
         * @param scoreToAdd The amount to add to the current score.
         */
        void addScore(int scoreToAdd);

        /**
         * @brief Setter for the maximum score of the client.
         * 
         * @param newMaxScore The new maximum score to set.
         */
        void setMaxScore(int newMaxScore);

        /**
         * @brief Setter for the client's name.
         * 
         * @param newName The new name to set.
         */
        void setName(std::string newName);

    private:
        std::size_t _clientID;  ///< The unique client ID.
        int _score;             ///< The client's current score.
        int _maxScore;          ///< The client's maximum score.
        std::string _name;      ///< The client's name.
};

#endif /* !CLIENTINWORLD_HPP_ */
