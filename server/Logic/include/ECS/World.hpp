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
#include <memory>
#include "Registry.hpp"
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include "../Components/Position.hpp"
#include "../Components/Velocity.hpp"
#include "../Components/Vitality.hpp"
#include "../Components/Projectile.hpp"
#include "../Components/Hitbox.hpp"
#include "../Components/Drawable.hpp"
#include "../Components/Bots/LinearShooter.hpp"
#include "../Components/Bots/TpShooter.hpp"
#include "../Components/Bots/SinusoidalShooter.hpp"
#include "../Components/Bots/KamikazeShooter.hpp"
#include "../Components/Bots/AlienEmperor.hpp"
#include "../Components/Bots/SpatialDustman.hpp"
#include "../Components/Bots/BigShip.hpp"
#include "../Components/Controllable.hpp"
#include "../Components/Clock.hpp"
#include "../Components/Ennemy.hpp"
#include "../Components/SpawnAfterDead.hpp"
#include "../Components/Force.hpp"
#include "../Components/Area.hpp"
#include "../Error/ErrorPasswordIncorrect.hpp"
#include "../Error/ErrorVector.hpp"
#include "../Error/ErrorWorldFull.hpp"
#include "../Error/ErrorClientAlreadyPresentInWorld.hpp"
#include "../VirtualKeyBoard.hpp"
#include "../GenerateWorld.hpp"
#include "../ClientInWorld.hpp"
#include "../SpawnRuleGenerator.hpp"
#include "../MyClock.hpp"

class CreateEntity;

/**
 * @class World
 * @brief Represents a game world that manages clients, levels, and world state.
 *
 * The `World` class handles the state of the game world, including client management,
 * world generation, and interaction with various game components like players, bots, and levels.
 */
class World {
public:

    enum STATE {
        NOTHING = 0,
        HOLD = 1,
        PLAY = 2
    };
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
     * @return A unordered_map containing clientID and class ClientInWorld.
     */
    std::unordered_map<std::size_t, ClientInWorld> &getClientsID() noexcept;

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
     * @return The class ClientInWorld removed from the world.
     */
    ClientInWorld deleteClientInWorld(std::size_t clientID);

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
     * @brief Spawn entities in world after generated world. After each call of the function, the generation
     *        is done farther
     * @param level The level to generate
     * @param spawnAfterWindow The beginning on the left side of the window to spawn entities
     * @param sizeWorld The size of the world to spawn entity
     *
     * @return A bool to indicate if the world is finished or not
     */
    bool spawnEntitiesInWorld(std::size_t level, std::size_t spawnAfterWindow, int sizeWorld);

    bool spawnEntitiesInWorld();

    /**
     * @brief Reset the boolean to indicates if the world if finished or not
     *
     * @param isWin To know if the level is ending by winning or not
     */
    void resetFinishedLevel(bool isWin);


    /**
     * @brief Get All Position, Type, Rotation and Rect for send to client.
     *
     * @return A list of Tuple containing the type(std::string), the postion in X-axis(float),
     *         the position in Y-axis(float), the rectwidth for animation on the spritesheet (float),
     *         the rectheight for animation on the spritesheet (float) and rotation of the sprite (float)
     */
    std::list<std::tuple<std::string, float, float, int, int, int, int, float>> getInformationOfEachEntity();

    /**
     * @brief Get Class to create entity
     *
     * @return The class CreateEntity
     */
    CreateEntity &getClassCreateEntity() noexcept;

    /**
     * @brief Spawn entity ID in world in ginven coordinates (origin top-left)
     * @param id ID of the entity
     * @param spawnInY Width-axis to spawn entity
     * @param spawnInX Height-axis to spawn entity
     * @param idAfterDead ID of the entity to spawn after his dead.
     *
     */
    void spawnEntityFromGeneratedWorld(std::size_t id, int spawnInX, int spawnInY, std::size_t idAfterDead = 0);

    const bool &getIsLevelFinishedToSpawn() const noexcept;
    void setIsLevelFinishedToSpawn(const bool &newState);

    MyClock &getClockGenerationWorld() noexcept;

    const int getBossIDAtTheEnd() const noexcept;

    const bool isBeginingOfSpwan() const noexcept;

    const float getSpawnTimeThreshold() const noexcept;

    const std::size_t getWidthWindow() const noexcept;
    const std::size_t getHeightWindow() const noexcept;
    const std::pair<std::size_t, std::size_t> getSizeWindow() const noexcept;

    void setWidthWindow(const std::size_t &newWidthWindow) noexcept;
    void setHeightWindow(const std::size_t &newHeightWindow) noexcept;
    void setSizeWindow(const std::pair<std::size_t, std::size_t> &newSizeWindow) noexcept;

    void applyFonctionInWorld();

    std::size_t getCurrentLevel() const noexcept;
    void setCurrentLevel(const std::size_t &newLevel) noexcept;

    void setStateOfTheWorld(const STATE &newState) noexcept;
    const STATE getStateOfTheWorld() const noexcept;

    SpawnRule::Generator &getClassSpawnRuleGenerator() noexcept;

    const bool &getIsForceInWorld() const noexcept;

    void setIsForceInWorld(const bool &newState) noexcept;

    const bool isEntityPresent(const std::size_t &entityIndex) noexcept;

private:
    STATE _stateWorld;                         ///< The State of the world.
    std::size_t _widthWindow;                  ///< Width of the window.
    std::size_t _heightWindow;                 ///< Height of the window.
    bool _isLevelFinishedToSpawn;              ///< Indicates if the world is finished to spawn.
    bool _isLevelFinished;                     ///< Indicates if the level is finished.
    int _spawnAfterWindow;                     ///< The x coordinates to spwan entites on the left side of the window.
    int _bossIDAtTheEnd;                       ///< The ID of the boss at the end (-1 if has no boss).
    bool _isClient;                            ///< Indicates if the world is client-based.
    bool _isPublic;                            ///< Indicates if the world is public.
    std::string _password;                     ///< The password for the world.
    int _nbrPlayerMax;                         ///< The maximum number of players in the world.
    std::string _nameRoom;                     ///< The name of the room.
    std::unordered_map<std::size_t, ClientInWorld> _idClients; ///< Map of client IDs in the world.
    Registry _r;                               ///< The registry holding game entities.
    sf::Clock _clock;                          ///< The clock tracking the world's time.
    MyClock _clockGenerationWorld;             ///< The clock tracking the world's time generation.
    static constexpr float SPAWN_TIME_THRESHOLD = 19.0f; ///< A Contante expression for the second elapsed to generate world
    static constexpr std::size_t SPAWN_AFTER_WINDOW = 400; ///< The value to spawn after the window (_widthWindow + SPAWN_AFTER_WINDOW)
    static constexpr std::size_t SIZE_WORLD = 4000; ///< The size of each world
    std::unordered_map<std::size_t, std::size_t> _seedByLevel; ///< Seeds for each level.
    std::size_t _maxLevel;                     ///< The maximum level.
    std::size_t _currentLevel;                 ///< The Level played.
    GenerateWorld _gw;                         ///< World generation helper.
    SpawnRule::Generator _srg;                 ///< Rule for generate world with perlin noise
    std::shared_ptr<CreateEntity> _ce;         ///< Class who allowed to create entity
    bool _isForceInWorld;                      ///< To determine if the force is present on the world.

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
    void addEntityInWorldSpawnRuleGenerator();

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
    std::vector<std::vector<SpawnRule::Generator::ENTITIES>> generateWorldWithEnum(
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
    std::vector<std::vector<SpawnRule::Generator::ENTITIES>> generateWorldWithEnum(
        std::size_t level,
        std::pair<float, float> &beginAndEndGenerationInX,
        std::pair<float, float> &beginAndEndGenerationInY
    );
};

#endif /* !WORLD_HPP_ */
