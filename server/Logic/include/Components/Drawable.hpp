/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Drawable
*/

#pragma once
#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Vector.hpp"

/**
 * @class Drawable
 * @brief A class representing an object that can be drawn on the screen.
 *
 * The Drawable class holds information about an image's path, sprite properties (such as animation, scale, and frame data),
 * and provides methods to access and modify these properties. It supports animated sprites with different frames for
 * various directions (up, down, left, right).
 */
class Drawable {
    public:
        /**
         * @brief Default constructor for the Drawable class.
         *
         * Initializes the Drawable object with default values.
         */
        Drawable();

        /**
         * @brief Parameterized constructor for the Drawable class.
         *
         * Initializes the Drawable object with specific values for the path, sprite sheet rectangle, animation,
         * scale, player status, and frame data for each direction (up, down, left, right).
         *
         * @param path The file path to the image (sprite sheet).
         * @param rect A vector containing the sprite sheet's position and size ([x, y, width, height]).
         * @param isAnimated A flag indicating if the sprite is animated.
         * @param scale The scale of the sprite.
         * @param player A flag indicating if the sprite represents a player.
         * @param frameUp Frame data for the sprite's "up" animation (optional).
         * @param frameDown Frame data for the sprite's "down" animation (optional).
         * @param frameLeft Frame data for the sprite's "left" animation (optional).
         * @param frameRight Frame data for the sprite's "right" animation (optional).
         */
        Drawable(std::string path, Vector<float, 4> rect, bool isAnimated, sf::Vector2f scale, bool player,
                std::vector<int> frameUp = {}, std::vector<int> frameDown = {}, std::vector<int> frameLeft = {}, std::vector<int> frameRight = {});

        /**
         * @brief Destructor for the Drawable class.
         *
         * Cleans up any resources used by the Drawable object.
         */
        ~Drawable();

        /**
         * @brief Gets the file path to the sprite image.
         *
         * @return The file path as a string.
         */
        std::string &getPath();

        /**
         * @brief Gets the rectangle defining the position and size of the sprite in the sprite sheet.
         *
         * @return A reference to the rectangle vector containing [x, y, width, height].
         */
        Vector<float, 4> &getRect();

        /**
         * @brief Gets the scaling factor for the sprite.
         *
         * @return A reference to the scaling factor as an sf::Vector2f.
         */
        sf::Vector2f &getScale();

        /**
         * @brief Checks if the sprite is animated.
         *
         * @return True if the sprite is animated, false otherwise.
         */
        bool getIsAnimate() const;

        /**
         * @brief Checks if the sprite represents a player.
         *
         * @return True if the sprite is for a player, false otherwise.
         */
        bool isPlayer() const;

        /**
         * @brief Gets the texture rectangle for the sprite.
         *
         * @return The texture rectangle as an sf::IntRect.
         */
        sf::IntRect getTextRect();

        /**
         * @brief Gets the frame data for the "up" animation.
         *
         * @return A vector containing the frame indices for the "up" animation.
         */
        std::vector<int> getFrameUp();

        /**
         * @brief Gets the frame data for the "down" animation.
         *
         * @return A vector containing the frame indices for the "down" animation.
         */
        std::vector<int> getFrameDown();

        /**
         * @brief Gets the frame data for the "left" animation.
         *
         * @return A vector containing the frame indices for the "left" animation.
         */
        std::vector<int> getFrameLeft();

        /**
         * @brief Gets the frame data for the "right" animation.
         *
         * @return A vector containing the frame indices for the "right" animation.
         */
        std::vector<int> getFrameRight();

        /**
         * @brief Sets the file path to the sprite image.
         *
         * @param newPath The new file path to set.
         */
        void setPath(std::string newPath);

        /**
         * @brief Sets the rectangle defining the position and size of the sprite in the sprite sheet.
         *
         * @param newRect A vector containing the new rectangle data [x, y, width, height].
         */
        void setRect(Vector<float, 4> newRect);

        /**
         * @brief Sets the scaling factor for the sprite.
         *
         * @param newScale The new scaling factor as an sf::Vector2f.
         */
        void setScale(sf::Vector2f newScale);

        /**
         * @brief Sets whether the sprite is animated.
         *
         * @param newIsAnimate True if the sprite should be animated, false otherwise.
         */
        void setIsAnimate(bool newIsAnimate);

        /**
         * @brief Sets whether the sprite represents a player.
         *
         * @param newPlayer True if the sprite represents a player, false otherwise.
         */
        void setPlayer(bool newPlayer);

        /**
         * @brief Sets the texture rectangle for the sprite.
         *
         * @param newTextRect The new texture rectangle as an sf::IntRect.
         */
        void setTextRect(sf::IntRect newTextRect);

        /**
         * @brief Sets the frame data for the "up" animation.
         *
         * @param newFrameUp A vector containing the new frame indices for the "up" animation.
         */
        void setFrameUp(std::vector<int> newFrameUp);

        /**
         * @brief Sets the frame data for the "down" animation.
         *
         * @param newFrameDown A vector containing the new frame indices for the "down" animation.
         */
        void setFrameDown(std::vector<int> newFrameDown);

        /**
         * @brief Sets the frame data for the "left" animation.
         *
         * @param newFrameLeft A vector containing the new frame indices for the "left" animation.
         */
        void setFrameLeft(std::vector<int> newFrameLeft);

        /**
         * @brief Sets the frame data for the "right" animation.
         *
         * @param newFrameRight A vector containing the new frame indices for the "right" animation.
         */
        void setFrameRight(std::vector<int> newFrameRight);

    protected:
    private:
        /**
         * @brief The file path to the sprite image.
         *
         * This private member stores the file path for the image (sprite sheet) used to draw the sprite.
         */
        std::string _path;

        /**
         * @brief The rectangle defining the position and size of the sprite in the sprite sheet.
         *
         * This private member defines the sprite's position and dimensions on the sprite sheet.
         */
        Vector<float, 4> _rect;

        /**
         * @brief The scale factor for the sprite.
         *
         * This private member defines how much to scale the sprite when rendering.
         */
        sf::Vector2f _scale;

        /**
         * @brief A flag indicating if the sprite is animated.
         *
         * This private member determines whether the sprite should be animated.
         */
        bool _isAnimated;

        /**
         * @brief A flag indicating if the sprite represents a player.
         *
         * This private member determines whether the sprite is used for a player character.
         */
        bool _player;

        /**
         * @brief The texture rectangle for the sprite.
         *
         * This private member defines the current frame or area of the sprite sheet to be used for drawing.
         */
        sf::IntRect _textRect;

        /**
         * @brief Frame data for the "up" animation.
         *
         * This private member stores the frame indices for the "up" animation.
         */
        std::vector<int> _frameUp;

        /**
         * @brief Frame data for the "down" animation.
         *
         * This private member stores the frame indices for the "down" animation.
         */
        std::vector<int> _frameDown;

        /**
         * @brief Frame data for the "left" animation.
         *
         * This private member stores the frame indices for the "left" animation.
         */
        std::vector<int> _frameLeft;

        /**
         * @brief Frame data for the "right" animation.
         *
         * This private member stores the frame indices for the "right" animation.
         */
        std::vector<int> _frameRight;

        /**
         * @brief The current frame of the animation.
         *
         * This private member keeps track of the current animation frame.
         */
        int currentFrame;
};

#endif /* !DRAWABLE_HPP_ */
