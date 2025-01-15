/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** WorldsIndex
*/

#ifndef WORLDSINDEX_HPP_
#define WORLDSINDEX_HPP_
#include <iostream>
#include <unordered_map>
#include "ECS/World.hpp"
#include "Systems.hpp"

/**
 * @class WorldsIndex
 * @brief Manages a collection of worlds, allowing creation, deletion, and retrieval by ID.
 *
 * The `WorldsIndex` class serves as a container for multiple `World` objects, enabling
 * operations such as adding new worlds, deleting existing ones, and querying the number
 * of worlds in the index.
 */
class WorldsIndex {
public:
    /**
     * @brief Constructs a new WorldsIndex object.
     */
    WorldsIndex();

    /**
     * @brief Destroys the WorldsIndex object and its contained worlds.
     */
    ~WorldsIndex();

    /**
     * @brief Retrieves a world by its unique ID.
     *
     * @param worldID The ID of the world to retrieve.
     *
     * @return A reference to the world with the given ID.
     */
    World &getWorldByID(std::size_t worldID);

    /**
     * @brief Retrieves all worlds in the index.
     *
     * @return A reference to the unordered map of worlds.
     */
    std::unordered_map<std::size_t, World> &getWorld();

    /**
     * @brief Adds a new world to the index.
     *
     * @param isClient Boolean indicating if the world is client-based.
     * @param isPublic Boolean indicating if the world is public.
     * @param nbrPlayerMax The maximum number of players allowed in the world.
     * @param nameRoom The name of the room.
     * @param clientID The client ID to associate with the world.
     * @param password Optional password for the world (default is empty).
     *
     * @return The ID of the newly added world.
     */
    std::size_t addWorld(
        bool isClient, bool isPublic, int nbrPlayerMax, std::string nameRoom,
        std::size_t clientID, std::string password = ""
    );

    /**
     * @brief Deletes a world from the index using its index.
     *
     * @param index The index of the world to delete.
     *
     * @return The world that was deleted.
     */
    World deleteWorld(std::size_t index);

    /**
     * @brief Deletes a world from the index using an iterator.
     *
     * @param it The iterator pointing to the world to delete.
     *
     * @return The world that was deleted.
     */
    World deleteWorld(std::unordered_map<std::size_t, World>::iterator it);

    /**
     * @brief Gets the number of worlds currently in the index.
     *
     * @return The number of worlds.
     */
    std::size_t getNbrWorlds() const noexcept;

    /**
     * @brief Apply all functions in each world for the Logic part
     */
    void applyFunctionsInWorlds();

private:
    Systems _systems;
    std::unordered_map<std::size_t, World> _wordMap; ///< The map of worlds indexed by their ID.
    std::size_t _nbrWorlds; ///< The current number of worlds in the index.
    std::size_t _nextIDWorld; ///< The ID to assign to the next world added.
};

#endif /* !WORLDSINDEX_HPP_ */
