/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Display
*/

/**
 * @file Display.hpp
 * @brief Header file for the Display class.
 */

#ifndef DISPLAY_HPP_
    #define DISPLAY_HPP_

    #include <iostream>
    #include "../Error/Error.hpp"
    #include <list>
    #include <map>
    #include <string>
    #include <functional>
    #include <SFML/Audio.hpp>
    #include <SFML/Graphics.hpp>
    #include <SFML/Window.hpp>
    #include <SFML/System.hpp>

/**
 * @class Display
 * @brief Handles rendering and interaction with graphical elements using SFML.
 */
class Display {
    public:
        /**
         * @brief Constructor that initializes the Display with a render window.
         * @param window Pointer to the SFML RenderWindow.
         */
        Display(sf::RenderWindow *window);

        /**
         * @brief Destructor for the Display class.
         */
        ~Display();

        /**
         * @brief Displays text on the screen.
         * @param message The text to be displayed.
         * @param fontPath Path to the font file.
         * @param sizeChar Size of the text characters.
         * @param color Color of the text.
         * @param position Position of the text on the screen.
         */
        void displayText(std::string message, std::string fontPath, int sizeChar, sf::Color color, sf::Vector2f position);

        /**
         * @brief Displays a rectangle on the screen.
         * @param color Color of the rectangle.
         * @param position Position of the rectangle on the screen.
         * @param size Size of the rectangle (width, height).
         */
        void displayRectangle(sf::Color color, sf::Vector2f position, sf::Vector2f size);

        /**
         * @brief Displays a button on the screen with associated functionality.
         * @param message Text to display on the button.
         * @param fontPath Path to the font file for the text.
         * @param sizeChar Size of the button text characters.
         * @param colorText Color of the button text.
         * @param colorBack Background color of the button.
         * @param position Position of the button on the screen.
         * @param size Size of the button (width, height).
         * @param function Callback function to be executed when the button is clicked.
         */
        void displayButton(std::string message, std::string fontPath, int sizeChar, sf::Color colorText,
            sf::Color colorBack, sf::Vector2f position, sf::Vector2f size, std::function<void()> function);

        /**
         * @brief Displays a sprite on the screen.
         * @param name Unique name for the sprite.
         * @param path Path to the sprite's image file.
         * @param position Position of the sprite on the screen.
         * @param scale Scaling factor for the sprite.
         * @param animationSecond Time in seconds for sprite animation (if applicable).
         */
        void displaySprite(std::string name, std::string path, sf::Vector2f position, sf::Vector2f scale, float animationSecond);

        /**
         * @brief Clears all registered buttons from the internal list.
         */
        void clearButtons();

        /**
         * @brief Retrieves the list of buttons.
         * @return A list of button bounding rectangles and their associated functions.
         */
        std::list<std::pair<sf::Rect<float>, std::function<void()>>> getButtons();

    protected:
    private:
        sf::RenderWindow *_window; ///< Pointer to the SFML RenderWindow used for rendering.
        std::list<std::pair<sf::Rect<float>, std::function<void()>>> _buttons; ///< List of buttons with bounding rectangles and associated functions.
        std::map<std::string, std::pair<sf::Rect<float>, sf::Clock>> _sprites; ///< Map of sprites with their bounding rectangles and clocks for animation.
};

#endif /* !DISPLAY_HPP_ */
