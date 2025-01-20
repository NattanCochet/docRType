/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Buttons
*/

#pragma once
#ifndef BUTTONS_HPP_
#define BUTTONS_HPP_
#include "../ECS/World.hpp"

/**
 * @class Buttons
 * @brief Class to manage and handle button actions in the game.
 *
 * This class is responsible for creating and handling various button actions
 * such as quitting the game, starting a game, navigating menus, etc.
 */
class Buttons
{
  public:
    /**
     * @brief Default constructor for the Buttons class.
     */
    Buttons();

    /**
     * @brief Constructor to initialize the Buttons class with a World object.
     *
     * @param world A pointer to the World object for accessing game state.
     */
    Buttons(World *world, Network *network);

    /**
     * @brief Destructor for the Buttons class.
     */
    ~Buttons();

    /**
     * @brief Handles the action for the quit button.
     *
     * This method is called when the quit button is pressed, allowing
     * the user to exit the game.
     *
     * @param index The index of the quit button.
     */
    void quitButton(std::size_t index);

    /**
     * @brief Handles the action for the play button.
     *
     * This method is called when the play button is pressed, allowing
     * the user to start the game.
     *
     * @param index The index of the play button.
     */
    void playButton(std::size_t index);

    /**
     * @brief Handles the action for the controls button.
     *
     * This method is called when the controls button is pressed, allowing
     * the user to navigate to the controls menu.
     *
     * @param index The index of the controls button.
     */
    void controlsButton(std::size_t index);

    /**
     * @brief Handles the action for the back button.
     *
     * This method is called when the back button is pressed, allowing
     * the user to go back to the previous menu or screen.
     *
     * @param index The index of the back button.
     */
    void backButton(std::size_t index);

    /**
     * @brief Handles the action for the join button.
     *
     * This method is called when the join button is pressed, allowing
     * the user to join a game or session.
     *
     * @param index The index of the join button.
     */
    void joinButton(std::size_t index);

    /**
     * @brief Handles the action for the start button.
     *
     * This method is called when the start button is pressed, allowing
     * the user to start a game or session.
     *
     * @param index The index of the start button.
     */
    void startButton(std::size_t index);

    /**
     * @brief Handles the action for the select button.
     *
     * This method is called when the select button is pressed, allowing
     * the user to select an option or item.
     *
     * @param index The index of the select button.
     */
    void selectButton(std::size_t index);

    void selectRoomButton(std::size_t index);

    void createMenuButton(std::size_t index);
    void reloadButton(std::size_t index);
    void createRoomButton(std::size_t index);
    void textButton(std::size_t index);
    void toggleButton(std::size_t index);
    void keyButton(std::size_t index);
    void nextRoomsPage(std::size_t index);
    void previousRoomsPage(std::size_t index);
    void unReadyButton(std::size_t index);

    typedef struct textButton_s {
        std::string _name;
        std::string _messageDefault;
    } textButton_t;

    typedef struct SplitButton_s {
        bool _active;
        std::size_t _index;
        sf::Color _defaultColor;
        sf::Color _activerColor;
        bool *_activePt;
        std::function<void(std::size_t)> _actionActivation;
        std::size_t _actionActivationParam;
        struct SplitButton_s *_other;
    } SplitButton_t;

    typedef struct KeyButton_s {
        sf::Keyboard::Key *_key;
        sf::Color _defaultColor;
        sf::Color _activeColor;
    } KeyButton_t;

    typedef struct NumButton_s {
        std::string _messageDefault;
    } NumButton_t;

    typedef struct BackButton_s {
        World::GAME_STATE _previousState;
    } BackButton_t;

    typedef struct RoomButton_s {
        bool _isPublic;
    } RoomButton_t;

    textButton_t *setTextButton(std::string name, std::string messageDefault, std::size_t index);
    NumButton_t *setNumButton(std::string messageDefault, std::size_t index);
    SplitButton_t *setSplitButton(sf::Color defaultColor, sf::Color activerColor, std::size_t index,
        bool *activePt = nullptr, std::function<void(std::size_t)> actionActivation = nullptr,
        std::size_t actionActivationParam = 0);
    KeyButton_t *setKeyButton(
        std::size_t index, sf::Keyboard::Key *key, sf::Color defaultColor, sf::Color activerColor);
    BackButton_t *setBackButton(std::size_t index, World::GAME_STATE previousState);
    RoomButton_t *setRoomButton(std::size_t index, bool isPublic);

    static void linkSplitButton(SplitButton_t *button_1, SplitButton_t *button_2);
    static bool writeKeyButton(sf::Keyboard::Key key, World &world, std::size_t index);
    static void writeNumButton(sf::Keyboard::Key key, World &world, std::size_t index);

  protected:
  private:
    /**
     * @brief A pointer to the World object that manages the game state.
     */
    World *_world;

    /**
     * @brief A list of pairs containing button hitboxes and their respective actions.
     *
     * The list contains pairs where the first element is the rectangle that
     * represents the button's area, and the second element is the function
     * that defines the action triggered by the button.
     */
    std::list<std::pair<sf::Rect<float>, std::function<void(std::size_t)>>> _buttons;
    std::map<std::size_t, Buttons::textButton_t> _listTextButton;
    std::map<std::size_t, Buttons::SplitButton_t> _listSplitButton;
    std::map<std::size_t, Buttons::KeyButton_t> _listKeyButton;
    std::map<std::size_t, Buttons::NumButton_t> _listNumButton;
    std::map<std::size_t, Buttons::BackButton_t> _listBackButton;
    std::map<std::size_t, Buttons::RoomButton_t> _listRoomButton;
    Network *_network;
};

#endif /* !BUTTONS_HPP_ */
