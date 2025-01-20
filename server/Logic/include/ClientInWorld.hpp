/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ClientInWorld
*/

#ifndef CLIENTINWORLD_HPP_
#define CLIENTINWORLD_HPP_
#include "Error/ErrorKeyNotFound.hpp"
#include <iostream>
#include <vector>

/**
 * @class ClientInWorld
 * @brief Represents a client within the game world, with properties like
 *        client ID, score, and name.
 *
 * This class is used to store and manage the client's information such as
 * their unique ID, score during the game, maximum score they have achieved,
 * and their name (defaulting to "Unknown").
 */
class ClientInWorld
{
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
     */
    ClientInWorld(std::size_t clientID, std::string name = "Unknown");

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
    const std::size_t &getMaxScorePerLevel(const std::size_t &level) const;

    /**
     * @brief Getter for the client's name.
     *
     * @return The name of the client.
     */
    const std::string &getName() const noexcept;

  public:
    /**
     * @brief Setter for the client ID.
     *
     * @param newClientID The new client ID to set.
     */
    void setClientID(const std::size_t &newClientID) noexcept;

    /**
     * @brief Adds a specified score to the client's current score.
     *
     * @param scoreToAdd The amount to add to the current score.
     */
    void addScore(const int scoreToAdd, const std::size_t scoringInLevel) noexcept;

    void saveScore() noexcept;

    void resetScore() noexcept;

    /**
     * @brief Setter for the client's name.
     *
     * @param newName The new name to set.
     */
    void setName(const std::string &newName) noexcept;

    void clientIsReady() noexcept;
    void clientIsntReady() noexcept;
    const bool &isReady() const noexcept;

    std::size_t &getRowSkin() noexcept;

    void setRowSkin(const std::size_t rowSkin) noexcept;

  private:
    std::size_t _clientID; ///< The unique client ID.
    std::size_t _currentLevel;
    int _score;                                 ///< The client's current score.
    std::vector<std::size_t> _maxScorePerLevel; ///< The client's maximum score.
    std::string _name;                          ///< The client's name.
    bool _isReady;                              ///< The client is ready to play or not
    std::size_t _rowSkin;                       ///< The skin row
};

#endif /* !CLIENTINWORLD_HPP_ */
