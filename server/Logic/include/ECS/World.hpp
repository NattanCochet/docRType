/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** World
*/

#pragma once
#ifndef WORLD_HPP_
#define WORLD_HPP_
#include <ctime>
#include <iostream>
#include <random>
#include <limits>
#include <unordered_map>
#include "Registry.hpp"
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include "../Components/Position.hpp"
#include "../Components/Velocity.hpp"
#include "../Components/Vitality.hpp"
#include "../Components/Projectile.hpp"
#include "../Components/Hitbox.hpp"
#include "../Components/Drawable.hpp"
#include "../Components/ABot.hpp"
#include "../Components/Bots/LinearShooter.hpp"
#include "../Components/Controllable.hpp"
#include "../Components/Clock.hpp"
#include "../Error/ErrorPasswordIncorrect.hpp"
#include "../Error/ErrorVector.hpp"
#include "../Error/ErrorWorldFull.hpp"
#include "../Error/ErrorClientAlreadyPresentInWorld.hpp"
#include "../VirtualKeyBoard.hpp"
#include "../GenerateWorld.hpp"
#include "../SpawnRuleGenerator.hpp"

/**
 * @class World
 * @brief Represents a game world that manages clients, levels, and world state.
 *
 * The `World` class handles the state of the game world, including client management,
 * world generation, and interaction with various game components like players, bots, and levels.
 */
class World {
public:
    /**
     * @brief Constructs a new World with specific parameters.
     *
     * @param client Boolean indicating if the world is for a client.
     * @param isPublic Boolean indicating if the world is public.
     * @param nbrPlayerMax The maximum number of players allowed in the world.
     * @param nameRoom The name of the room.
     * @param clientID The unique client ID.
     * @param password Optional password for the world (default is empty).
     */
    World(
        bool client, bool isPublic, int nbrPlayerMax, std::string nameRoom,
        std::size_t clientID, std::string password = ""
    );

    /**
     * @brief Default constructor.
     */
    World();

    /**
     * @brief Destructor for the World class.
     */
    ~World() = default;

    /**
     * @brief Gets the world registry containing all game entities.
     *
     * @return The registry of the world.
     */
    Registry &getRegistry();

    /**
     * @brief Gets the clock used to track the world's time.
     *
     * @return The world's clock.
     */
    sf::Clock &getClock();

    /**
     * @brief Checks if the world is a client-based world.
     *
     * @return True if the world is client-based, false otherwise.
     */
    bool isWorldIsClient() const noexcept;

    /**
     * @brief Checks if the world is public.
     *
     * @return True if the world is public, false otherwise.
     */
    bool isWorldIsPublic() const noexcept;

    /**
     * @brief Checks if the world is full (has reached the maximum number of players).
     *
     * @return True if the world is full, false otherwise.
     */
    bool isWorldFull() const noexcept;

    /**
     * @brief Gets the name of the world.
     *
     * @return The name of the world.
     */
    std::string getNameOfWorld() const noexcept;

    /**
     * @brief Changes the parameters of the world.
     *
     * @param client Boolean indicating if the world is for a client.
     * @param isPublic Boolean indicating if the world is public.
     * @param nbrPlayerMax The maximum number of players allowed in the world.
     * @param nameRoom The name of the room.
     * @param password Optional password for the world (default is empty).
     */
    void changeParametersOfWorld(
        bool client, bool isPublic, int nbrPlayerMax, std::string nameRoom,
        std::string password = ""
    ) noexcept;

    /**
     * @brief Gets the list of client IDs in the world.
     *
     * @return A vector containing the client IDs.
     */
    std::vector<std::size_t> getClientsID() const noexcept;

    /**
     * @brief Adds a client to the world.
     *
     * @param clientID The client ID to add.
     * @param password The password for the world (if required).
     *
     * @return The client ID added to the world.
     */
    std::size_t addClientInWorld(std::size_t clientID, std::string password);

    /**
     * @brief Removes a client from the world.
     *
     * @param clientID The client ID to remove.
     *
     * @return The client ID removed from the world.
     */
    std::size_t deleteClientInWorld(std::size_t clientID);

    /**
     * @brief Checks if a client with the given ID is present in the world.
     *
     * @param clientID The client ID to check.
     *
     * @return True if the client is present, false otherwise.
     */
    bool isClientIDPresentAsBool(std::size_t clientID) noexcept;

    /**
     * @brief Gets the presence status of a client by their ID as an integer.
     *
     * @param clientID The client ID to check.
     *
     * @return clientID if the client is present, -1 otherwise.
     */
    int getClientIDPresenceAsInt(std::size_t clientID) noexcept;

    /**
     * @brief Changes the value of a key for a specific client.
     *
     * @param clientID The client ID.
     * @param key The control key to update.
     * @param isPressed Boolean indicating if the key is pressed.
     */
    void changeValueOfKeyPerClientID(std::size_t clienID, VirtualKeyBoard::CONTROL key, bool isPressed);

    /**
     * @brief Changes the value of a key for a specific client using a tuple of client ID, key, and key state.
     *
     * @param action A tuple containing the client ID, control key, and key state.
     */
    void changeValueOfKeyPerClientID(std::tuple<std::size_t, VirtualKeyBoard::CONTROL, bool> action);

    /**
     * @brief Gets the virtual keyboard associated with a client ID.
     *
     * @param clientID The client ID.
     *
     * @return The virtual keyboard for the client.
     */
    VirtualKeyBoard &getVirtualKeyBoardFromClientID(std::size_t clientID);

    /**
     * @brief Gets the map of virtual keyboards for all clients in the world.
     *
     * @return The map of virtual keyboards keyed by client IDs.
     */
    std::unordered_map<std::size_t, VirtualKeyBoard> &getVirtualKeyBoard() noexcept;

    /**
     * @brief Generates the next seed for the next level.
     */
    void generateNextSeedForNextLevel();

    /**
     * @brief Gets the maximum level available in the world.
     *
     * @return The maximum level number.
     */
    std::size_t getMaxLevel() const noexcept;

    /**
     * @brief Gets the seed for a specific level.
     *
     * @param level The level number.
     *
     * @return The seed for the specified level.
     */
    std::size_t getSeedForLevel(const std::size_t &level);

    /**
     * @brief Generates the world for the next level with floating point ranges.
     *
     * @param level The level number.
     * @param beginAndEndGenerationInX The range for world generation along the X-axis.
     * @param beginAndEndGenerationInY The range for world generation along the Y-axis.
     *
     * @return A 2D vector representing the world with ID of entities.
     */
    std::vector<std::vector<int>> generateWorldWithID(
        std::size_t level,
        std::pair<float, float> &beginAndEndGenerationInX,
        std::pair<float, float> &beginAndEndGenerationInY
    );

    /**
     * @brief Generates the world for the next level with integer ranges.
     *
     * @param level The level number.
     * @param beginAndEndGenerationInX The range for world generation along the X-axis.
     * @param beginAndEndGenerationInY The range for world generation along the Y-axis.
     *
     * @return A 2D vector representing the world with ID of entities.
     */
    std::vector<std::vector<int>> generateWorldWithID(
        std::size_t level,
        std::pair<int, int> &beginAndEndGenerationInX,
        std::pair<int, int> &beginAndEndGenerationInY
    );

    /**
     * @brief Generates the world for the next level with integer ranges.
     *
     * @param level The level number.
     * @param beginAndEndGenerationInX The range for world generation along the X-axis.
     * @param beginAndEndGenerationInY The range for world generation along the Y-axis.
     *
     * @return A 2D vector representing the world with ENUM of entities.
     */
    std::vector<std::vector<SpawnRuleGenerator::ENTITIES>> generateWorldWithEnum(
        std::size_t level,
        std::pair<int, int> &beginAndEndGenerationInX,
        std::pair<int, int> &beginAndEndGenerationInY
    );

    /**
     * @brief Generates the world for the next level with floating point ranges.
     *
     * @param level The level number.
     * @param beginAndEndGenerationInX The range for world generation along the X-axis.
     * @param beginAndEndGenerationInY The range for world generation along the Y-axis.
     *
     * @return A 2D vector representing the world with ENUM of entities.
     */
    std::vector<std::vector<SpawnRuleGenerator::ENTITIES>> generateWorldWithEnum(
        std::size_t level,
        std::pair<float, float> &beginAndEndGenerationInX,
        std::pair<float, float> &beginAndEndGenerationInY
    );


    /**
     * @brief Get All Position, Type, Rotation and Rect for send to client.
     *
     * @return A list of Tuple containing the type(std::string), the postion in X-axis(float),
     *         the position in Y-axis(float), the rectwidth for animation on the spritesheet (float),
     *         the rectheight for animation on the spritesheet (float) and rotation of the sprite (float)
     */
    std::list<std::tuple<std::string, float, float, float, float, float>> getInformationOfEachEntity();

private:
    bool _isClient;                            ///< Indicates if the world is client-based.
    bool _isPublic;                            ///< Indicates if the world is public.
    std::string _password;                     ///< The password for the world.
    int _nbrPlayerMax;                         ///< The maximum number of players in the world.
    std::string _nameRoom;                     ///< The name of the room.
    std::vector<std::size_t> _idClients;       ///< List of client IDs in the world.
    Registry _r;                               ///< The registry holding game entities.
    sf::Clock _clock;                          ///< The clock tracking the world's time.
    std::unordered_map<std::size_t, VirtualKeyBoard> _virtualKeyBoardPerClientID; ///< Virtual keyboards by client ID.
    std::unordered_map<std::size_t, std::size_t> _seedByLevel; ///< Seeds for each level.
    std::size_t _maxLevel;                     ///< The maximum level.
    GenerateWorld _gw;                         ///< World generation helper.
    SpawnRuleGenerator _srg;                   ///< Rule for generate world with perlin noise

private:
    /**
     * @brief Checks if the provided password matches the world's password.
     *
     * @param password The password to check.
     *
     * @return True if the passwords match, false otherwise.
     */
    bool isSamePassword(std::string password) const noexcept;

    /**
     * @brief Add All Entities in class SpawnRuleGenerator, all entities possible to spawn
     *
     */
    void addEntityInWroldSpawnRuleGenerator();
};

#endif /* !WORLD_HPP_ */
