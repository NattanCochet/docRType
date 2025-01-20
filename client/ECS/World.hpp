/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** World
*/

/**
 * @file World.hpp
 * @brief Header file for the World class, which manages the game world and handles key and mouse actions.
 *
 * The World class is responsible for the core game state, including the management of entities through the Registry,
 * handling user input (keyboard and mouse), and providing access to game assets like textures and fonts.
 * It also manages the game clock and the state of the game (e.g., menu, in-game, etc.).
 */

#pragma once
#ifndef WORLD_HPP_
#define WORLD_HPP_

#include "../Network/Network.hpp"
#include "Assets.hpp"
#include "Components/Position.hpp"
#include "Components/Clickable.hpp"
#include "Components/ControlsEnum.hpp"
#include "Components/Controllable.hpp"
#include "Components/Drawable.hpp"
#include "Registry.hpp"
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <ctime>
#include <iostream>
#include <set>
// #include "../Components/Projectile.hpp"

class World
{
    public:
        /**
         * @brief Constructor for the World class.
         *
         * Initializes the world with the client/server mode and sets up the render window.
         *
         * @param isClient Indicates whether the world is being initialized for a client or server.
         * @param window A pointer to the SFML render window used for rendering.
         */
        World(bool isClient, sf::RenderWindow *window);

        /**
         * @brief Destructor for the World class.
         *
         * Cleans up resources used by the world, such as window and assets.
         */
        ~World() = default;

        /**
         * @brief Enumeration for press/release states of a key.
         */
        enum PRESS {
            PRESSED, /**< Key has been pressed. */
            RELEASED /**< Key has been released. */
        };

        /**
         * @brief Enumeration for the different game states.
         */
        enum GAME_STATE {
            MENU,         /**< The game is in the menu state. */
            NETWORK_MENU, /**< The game is in the network menu state. */
            CREATE_ROOM,
            IN_GAME,       /**< The game is in the in-game state. */
            CONTROLS_MENU, /**< The game is in the controls menu state. */
            LOBBY_MENU     /**< The game is in the lobby menu state. */
        };

        /**
         * @brief Gets the registry managing the entities and components in the world.
         *
         * @return The Registry instance of the world.
         */
        Registry &getRegistry();

        Registry &getOnlineRegistry();

        /**
         * @brief Gets the clock used to measure elapsed time in the world.
         *
         * @return A reference to the SFML clock.
         */
        sf::Clock &getClock();

        /**
         * @brief Loads a sprite from a file and returns a pointer to it.
         *
         * @param filepath The path to the sprite file.
         * @return A pointer to the loaded SFML sprite.
         */
        sf::Sprite *getSprite(std::string filepath);

        /**
         * @brief Loads a text from a file and returns a pointer to it.
         *
         * @param filepath The path to the text file.
         * @return A pointer to the loaded SFML text.
         */
        sf::Text *getText(std::string filepath);

        /**
         * @brief Loads a rectangle shape from a file and returns a pointer to it.
         *
         * @param name The name of the rectangle shape.
         * @return A pointer to the loaded SFML rectangle shape.
         */
        sf::RectangleShape *getRectangle(std::string name);

        /**
         * @brief Gets the window used for rendering the world.
         *
         * @return A pointer to the SFML render window.
         */
        sf::RenderWindow *getWindow();

        /**
         * @brief Adds a key action to the world for the specified press state and key.
         *
         * @param press The press state (PRESSED or RELEASED).
         * @param key The key that was pressed or released.
         */
        void addKeyAction(PRESS press, sf::Keyboard::Key key);

        /**
         * @brief Clears all recorded key actions from the world.
         */
        void clearKeyAction();

        std::vector<std::pair<PRESS, sf::Keyboard::Key>> getKeyActions();

        /**
         * @brief Adds a mouse action to the world for the specified press state and mouse position.
         *
         * @param press The press state (PRESSED or RELEASED).
         * @param pos The position of the mouse when the action occurred.
         */
        void addMouseAction(PRESS press, sf::Vector2i pos);

        /**
         * @brief Clears all recorded mouse actions from the world.
         */
        void clearMouseAction();

        /**
         * @brief Gets the list of recorded mouse actions in the world.
         *
         * @return A reference to a vector of mouse actions.
         */
        std::vector<std::pair<World::PRESS, sf::Vector2i>> &getMouseAction();

        /**
         * @brief Sets the current state of the game.
         *
         * @param state The new game state (e.g., MENU, IN_GAME).
         */
        void setState(GAME_STATE state);

        /**
         * @brief Gets the current state of the game.
         *
         * @return The current game state.
         */
        GAME_STATE getState(void);

        /**
         * @brief Sets the previous state of the game.
         *
         * @param state The old game state (e.g., MENU, IN_GAME).
         */
        void setPreviousState(GAME_STATE state);

        /**
         * @brief Gets the previous state of the game.
         *
         * @return The previous game state.
         */
        GAME_STATE getPreviousState(void);

        /**
         * @brief Sets the room name for the game.
         *
         * @param roomName The name of the room.
         */
        void setRoomName(std::string roomName);

        /**
         * @brief Gets the current room name.
         *
         * @return The current room name.
         */
        std::string getRoomName(void);

        void setRoomPassword(std::string roomPassword);
        std::string getRoomPassword(void);
        void setInputButtonIndex(const std::string &name, std::size_t index);
        std::size_t getInputButtonIndex(const std::string &name);
        void setTextWritting(int textWritting);
        int getTextWritting(void);
        void setControlWritting(int controlWritting);
        int getControlWritting(void);
        int getNbEntities();
        void setNbEntities(int nbEntities);
        int getNbEntitiesOnline();
        void setNbEntitiesOnline(int nbEntities);
        NetworkClient &getClient();
        std::map<std::string, int> &getKeysIndex();
        void resetKeysIndex();
        void addRoomsList(std::tuple<std::size_t, bool, std::size_t, std::size_t, std::string> newRoom);
        void clearRoomsList();
        std::vector<std::tuple<std::size_t, bool, std::size_t, std::size_t, std::string>> getRoomsList();
        void setPageNumber(std::pair<int, std::size_t> newPageNumber);
        std::pair<int, std::size_t> getPageNumber();
        void setRoomIndex(std::size_t newIndex);
        std::size_t getRoomIndex();
        void setNbInRoom(std::pair<std::size_t, std::size_t> newNb);
        std::pair<std::size_t, std::size_t> getNbInRoom();
        void setLocalPlayer(int newIndex);
        int getLocalPlayer();
        bool getServerConnection();
        void setServerConnection(bool newServerConnection);

    private:
        bool _isClient;            /**< Indicates whether the world is in client mode. */
        Registry _r;               /**< The registry that manages the entities and components. */
        Registry _rOnline;         /**< The registry that manages the entities and components from server. */
        sf::Clock _clock;          /**< The clock for measuring elapsed time. */
        Assets _assets;            /**< The assets used in the game (textures, fonts, etc.). */
        sf::RenderWindow *_window; /**< The render window used for displaying the game. */
        std::vector<std::pair<PRESS, sf::Keyboard::Key>> _keyActions; /**< The list of recorded key actions. */
        std::vector<std::pair<PRESS, sf::Vector2i>> _mouseActions;    /**< The list of recorded mouse actions. */
        GAME_STATE _state;     /**< The current state of the game (e.g., MENU, IN_GAME). */
        GAME_STATE _prevState; /**< The previous state of the game (e.g., MENU, IN_GAME). */
        std::size_t _idRoom;
        std::string _roomName; /**< The current room name. */
        std::string _roomPassword;
        std::size_t _roomIndex;
        std::pair<std::size_t, std::size_t> _nbInRoom;
        std::map<std::string, std::size_t> _buttonsTextInputs;
        std::size_t _nbEntities;       /**< The number of entities in the game world. */
        std::size_t _nbEntitiesOnline; /**< The number of entities in the server world. */
        std::size_t _textWritting;
        std::size_t _controlWritting;
        NetworkClient _client;
        std::map<std::string, int> _keysIndex;
        std::vector<std::tuple<std::size_t, bool, std::size_t, std::size_t, std::string>> _roomsList;
        std::pair<int, std::size_t> _pageNumber;
        int _indexLocalPlayer;
        bool _serverConnection;

    public:
        std::map<CONTROL, sf::Keyboard::Key> _controlsMap;
};

#endif /* !WORLD_HPP_ */
