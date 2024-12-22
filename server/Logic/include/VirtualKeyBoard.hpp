/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** VirtualKeyBoard
*/

#ifndef VIRTUALKEYBOARD_HPP_
#define VIRTUALKEYBOARD_HPP_
#include <unordered_map>

/**
 * @class VirtualKeyBoard
 * @brief Represents a virtual keyboard for controlling game actions.
 *
 * The `VirtualKeyBoard` class manages a set of control keys and their states (pressed or not).
 * It provides methods to modify and check the state of the controls (e.g., UP, DOWN, LEFT, RIGHT, SHOOT, FORCE, START).
 */
class VirtualKeyBoard
{
    public:
        /**
         * @enum CONTROL
         * @brief Enum for defining the control keys available on the virtual keyboard.
         *
         * The `CONTROL` enum defines the various control keys that can be mapped to actions
         * in the game, such as movement directions or triggering actions.
         */
        enum CONTROL {
            UP = 0,    ///< Control for moving up.
            DOWN = 1,  ///< Control for moving down.
            LEFT = 2,  ///< Control for moving left.
            RIGHT = 3, ///< Control for moving right.
            SHOOT = 4, ///< Control for shooting.
            FORCE = 5, ///< Control for activating a force action.
            START = 6, ///< Control for starting the game.
        };

        /**
         * @brief Default constructor that initializes the virtual keyboard state.
         *
         * Initializes the control keys to `false`, indicating they are not pressed.
         */
        VirtualKeyBoard();

        /**
         * @brief Destructor.
         *
         * The destructor does not need to perform any special cleanup.
         */
        ~VirtualKeyBoard();

        /**
         * @brief Retrieves a reference to the internal virtual keyboard state.
         *
         * @return A reference to the `unordered_map` that holds the state of the controls.
         */
        std::unordered_map<CONTROL, bool> &getVirtualKeyboard() noexcept;

        /**
         * @brief Changes the state of a specific control key.
         *
         * @param key The control key whose state will be changed.
         * @param isPressed The new state of the control key (true for pressed, false for not pressed).
         */
        void changeValueKeyboard(CONTROL key, bool isPressed) noexcept;

        /**
         * @brief Checks if a specific control key is pressed.
         *
         * @param key The control key to check.
         * @return `true` if the key is pressed, `false` otherwise.
         */
        bool isKeyIsPressed(CONTROL key);

        /**
         * @brief Get if the user is charging a shoot or not
         *
         * @return `true` if the key shoot is pressed, `false` otherwise.
         */
        bool isCharging();

        /**
         * @brief Set if user is charging a shoot or not
         *
         * @param isCharging Set is charging or not
         */
        void setIsCharging(bool isCharging);

    private:
        std::unordered_map<CONTROL, bool> _virtualKeyboard; ///< Internal state of the virtual keyboard, mapping each control to its pressed state.
        bool _isCharging; ///< Bool to know if the user is charging his shoot or not.
};

#endif /* !VIRTUALKEYBOARD_HPP_ */
