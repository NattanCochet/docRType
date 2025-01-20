/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Drawable
*/

/**
 * @file Drawable.hpp
 * @brief Header file for the Drawable class.
 */

#pragma once
#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <functional>
#include <list>
#include "../../Error/Error.hpp"

/**
 * @class Drawable
 * @brief Class for objects that can be drawn on the screen, such as sprites, text, and buttons.
 * 
 * This class represents graphical objects that can be rendered to the screen. It supports
 * sprites, text, and buttons with properties like scaling, color, animation, and more.
 */
class Drawable {
    public:
        /**
         * @enum typeSFML
         * @brief Enumeration of the types of drawable objects.
         */
        enum typeSFML {
            SPRITE, /**< A sprite object. */
            TEXT,   /**< A text object. */
            BUTTON  /**< A button object. */
        };

        /**
         * @brief Default constructor for the Drawable class.
         */
        Drawable();

        /**
         * @brief Constructor for a sprite object.
         * @param path Path to the image file.
         * @param kind Type of the drawable object (SPRITE).
         * @param scale Scale factor for the sprite.
         * @param rect Rectangle defining the sprite frame (position, size).
         */
        Drawable(std::string path, typeSFML kind, sf::Vector2f scale, sf::IntRect rect, float angle);

        /**
         * @brief Constructor for a text object.
         * @param fontPath Path to the font file.
         * @param kind Type of the drawable object (TEXT).
         * @param scale Scale factor for the text.
         * @param message The message to be displayed.
         * @param sizeChar Size of the text characters.
         * @param color Text color.
         */
        Drawable(std::string fontPath, typeSFML kind, sf::Vector2f scale, std::string message, std::size_t sizeChar, sf::Color color, float angle);

        /**
         * @brief Constructor for a button object.
         * @param fontPath Path to the font file.
         * @param kind Type of the drawable object (BUTTON).
         * @param scale Scale factor for the button.
         * @param message The message displayed on the button.
         * @param sizeChar Size of the text characters.
         * @param colorText Color of the button text.
         * @param colorBack Background color of the button.
         * @param size Size of the button (width, height).
         */
        Drawable(std::string fontPath, typeSFML kind, sf::Vector2f scale, std::string message, std::size_t sizeChar, sf::Color colorText,
        sf::Color colorBack, sf::Vector2f size, float angle);

        /**
         * @brief Destructor for the Drawable class.
         */
        ~Drawable();

        /**
         * @brief Gets the path to the image or font file.
         * @return A reference to the file path string.
         */
        std::string &getPath();

        /**
         * @brief Gets the rectangle that defines the sprite's frame.
         * @return A pointer to the sf::IntRect representing the sprite's frame.
         */
        sf::IntRect *getRect();

        /**
         * @brief Gets the text color.
         * @return A reference to the color of the text.
         */
        sf::Color &getColorText();

        /**
         * @brief Gets the background color.
         * @return A reference to the background color.
         */
        sf::Color &getColor();

        /**
         * @brief Gets the scale factor for the drawable object.
         * @return A reference to the scale vector.
         */
        sf::Vector2f &getScale();

        /**
         * @brief Gets the message associated with the drawable object (for text or button).
         * @return The message string.
         */
        std::string getMessage();

        /**
         * @brief Gets the size of the text characters.
         * @return The character size.
         */
        size_t getSizeChar();

        /**
         * @brief Gets the size of the rectangle (for buttons).
         * @return The size vector (width, height).
         */
        sf::Vector2f getSizeRectangle();

        /**
         * @brief Checks if the drawable object is animated.
         * @return True if the object is animated, false otherwise.
         */
        bool getIsAnimate() const;

        /**
         * @brief Gets the clock used for animation timing.
         * @return A pointer to the sf::Clock used for animation.
         */
        sf::Clock *getClock();

        /**
         * @brief Restarts the animation clock.
         */
        void restartClock();

        /**
         * @brief Sets the path to the image or font file.
         * @param newPath New file path.
         */
        void setPath(std::string newPath);

        /**
         * @brief Sets the rectangle that defines the sprite's frame.
         * @param newRect New sf::IntRect for the sprite's frame.
         */
        void setRect(sf::IntRect newRect);

        /**
         * @brief Sets the text color.
         * @param newtColor New color for the text.
         */
        void setColorText(sf::Color newtColor);

        /**
         * @brief Sets the background color.
         * @param newtColor New background color.
         */
        void setColor(sf::Color newtColor);

        /**
         * @brief Sets the scale factor for the drawable object.
         * @param newScale New scale vector.
         */
        void setScale(sf::Vector2f newScale);

        /**
         * @brief Sets whether the object is animated.
         * @param newIsAnimate True for animated, false for static.
         */
        void setIsAnimate(bool newIsAnimate);

        /**
         * @brief Sets the message associated with the drawable object (for text or button).
         * @param message New message to display.
         */
        void setMessage(std::string message);

        /**
         * @brief Sets the size of the text characters.
         * @param sizeChar New size for text characters.
         */
        void setSizeChar(size_t sizeChar);

        /**
         * @brief Sets the size of the rectangle (for buttons).
         * @param sizeRectangle New size for the button rectangle.
         */
        void setSizeRectangle(sf::Vector2f sizeRectangle);

        float getAngle();
        void setAngle(float newAngle);

        /**
         * @brief Gets the type of the drawable object.
         * @return The type of the object (SPRITE, TEXT, BUTTON).
         */
        typeSFML getKind() const;

    protected:
    private:
        std::string _path; ///< Path to the image or font file.
        sf::IntRect _rect; ///< Rectangle defining the sprite's frame.
        sf::Color _colorText; ///< Color of the text (for text and buttons).
        sf::Color _color; ///< Background color (for buttons).
        sf::Vector2f _scale; ///< Scale factor for the object.
        bool _isAnimate; ///< Whether the object is animated.
        typeSFML _kind; ///< Type of the drawable object (sprite, text, or button).
        std::string _message; ///< Message for text or button objects.
        std::size_t _sizeChar; ///< Size of text characters.
        sf::Vector2f _size; ///< Size of the rectangle (for buttons).
        sf::Clock _clock; ///< Clock for animation timing.
        float _angle;
};

#endif /* !DRAWABLE_HPP_ */
