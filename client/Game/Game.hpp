/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Game
*/
/**
 * @file Game.hpp
 * @brief Header file for the Game class that handles the main game loop, event handling,
 *        and entity management within the game.
 *
 * The Game class encapsulates the main logic of the game, including the initialization of entities,
 * the event handling, and the management of different game states.
 */
#pragma once
#ifndef GAME_HPP_
#define GAME_HPP_
#include "../Buttons/Buttons.hpp"
#include "../ECS/Components/ControlsEnum.hpp"
#include "../ECS/Systems.hpp"
#include "../ECS/World.hpp"

#ifdef _WIN32
#define PATH "../../" /**< Define the path based on the OS, using relative paths for Windows. */
#else
#define PATH "../" /**< Define the path for Unix-based systems using relative paths. */
#endif

class Game
{
  public:
    /**
     * @brief Default constructor for the Game class.
     *
     * Initializes the game, including the window, display, and world objects.
     */
    Game();

    /**
     * @brief Destructor for the Game class.
     *
     * Cleans up any resources allocated by the Game class during the lifetime of the object.
     */
    ~Game();

    int init();

    /**
     * @brief Main game loop that handles the game play.
     *
     * This function manages the game state, updates entities, processes events, and renders the game.
     */
    void play();

  private:
    /**
     * @brief Handles events such as keyboard, mouse, and window events.
     *
     * This function processes user input and window events.
     *
     * @return An integer indicating the result of the event handling.
     */
    int event();

    /**
     * @brief Initializes new entities based on the current game state.
     *
     * This function creates the necessary entities when transitioning to a new game state.
     *
     * @param r The Registry used for managing entities.
     * @param newState The new game state to initialize entities for.
     */
    void initNewEntities(Registry &r, World::GAME_STATE newState);

    /**
     * @brief Destroys all entities in the current game state.
     *
     * This function removes all active entities from the game world.
     *
     * @param r The Registry used for managing entities.
     */
    void killAllEntities(Registry &r);

    /**
     * @brief Initializes entities for the menu state.
     *
     * This function sets up the entities required for the game menu.
     *
     * @param r The Registry used for managing entities.
     */
    void initMenuEntities(Registry &r);

    /**
     * @brief Initializes entities for the network menu state.
     *
     * This function sets up the entities required for the network menu.
     *
     * @param r The Registry used for managing entities.
     */
    void initNetworkMenuEntities(Registry &r);

    void initCreateRoomEntities(Registry &r);

    /**
     * @brief Initializes entities for the in-game state.
     *
     * This function sets up the entities required for the in-game state.
     *
     * @param r The Registry used for managing entities.
     */
    void initInGameEntities(Registry &r);

    /**
     * @brief Initializes entities for the controls menu state.
     *
     * This function sets up the entities required for the controls menu.
     *
     * @param r The Registry used for managing entities.
     */
    void initControlsMenuEntities(Registry &r);

    /**
     * @brief Initializes entities for the lobby menu state.
     *
     * This function sets up the entities required for the lobby menu.
     *
     * @param r The Registry used for managing entities.
     */
    void initLobbyMenuEntities(Registry &r);

    /**
     * @brief Processes all the entities and systems for the given game state.
     *
     * This function updates entities, processes systems, and manages the game state.
     *
     * @param r The Registry used for managing entities.
     * @param state The current game state.
     */
    void allProcess(Registry &r, World::GAME_STATE state, int begin);

    /**
     * @brief Processes network-related actions.
     *
     * This function handles network interactions and updates related to multiplayer gameplay.
     *
     * @param r The Registry used for managing entities.
     */
    void printRooms(Registry &r, int begin);

    void moveCreateRoomPasswordButtonAway(std::size_t index);
    void moveCreateRoomPasswordButtonBack(std::size_t index);

  private:
    sf::RenderWindow _window; /**< The render window used for displaying the game. */
    sf::Event _event;         /**< The event object used for handling events. */
    int _fps;                 /**< The frame rate of the game. */
    World *_world;            /**< The world object containing the game entities and systems. */
    Buttons _buttons;         /**< The button system for handling user interactions. */
    std::size_t _nbRooms;     /**< The number of rooms in the game. */
    Network _network;
    size_t _roomsPage;
};

#endif /* !GAME_HPP_ */
