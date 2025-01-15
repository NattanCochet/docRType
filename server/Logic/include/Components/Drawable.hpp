/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Drawable
*/

/**
 * @file Drawable.hpp
 * @brief Declaration of the Drawable class, which represents an object that can be drawn on the screen.
 */

#pragma once
#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Vector.hpp"
#include "../Error/ErrorNoObject.hpp"

namespace Drawable
{
    /**
     * @class FrameRect
     * @brief Represents a frame of the sprite in the sprite sheet.
     * 
     * FrameRect holds the position and dimensions of a frame in the sprite sheet.
     */
    class FrameRect
    {
        public:
            /**
             * @brief Constructor for FrameRect.
             *
             * Initializes the frame rectangle with the provided position and size.
             * 
             * @param rectLeft The left position of the rectangle in the sprite sheet.
             * @param rectTop The top position of the rectangle in the sprite sheet.
             * @param rectWidth The width of the rectangle in the sprite sheet.
             * @param rectHeight The height of the rectangle in the sprite sheet.
             */
            FrameRect(int rectLeft, int rectTop, int rectWidth, int rectHeight);

            /**
             * @brief Destructor for FrameRect.
             */
            ~FrameRect() = default;

        public:
            int _rectLeft;  /**< Left position of the frame in the sprite sheet */
            int _rectTop;   /**< Top position of the frame in the sprite sheet */
            int _rectWidth; /**< Width of the frame in the sprite sheet */
            int _rectHeight; /**< Height of the frame in the sprite sheet */
    };

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
             * @brief Parameterized constructor for the Drawable class.
             *
             * Initializes the Drawable object with specific values for the path, sprite sheet rectangle, animation,
             * scale, player status, and frame data for each direction (up, down, left, right).
             * 
             * @param type The type of the drawable object (e.g., "player", "enemy").
             * @param isAnimated A flag indicating if the sprite is animated.
             * @param scale The scale of the sprite.
             * @param defaultFrame Frame data for the default (static) animation.
             * @param secondForDefaultFrame Duration for each frame of the default animation.
             * @param frameUP Frame data for the "up" animation.
             * @param secondForFrameUp Duration for each frame of the "up" animation.
             * @param frameDown Frame data for the "down" animation.
             * @param secondForFrameDown Duration for each frame of the "down" animation.
             * @param frameLeft Frame data for the "left" animation.
             * @param secondForFrameLeft Duration for each frame of the "left" animation.
             * @param frameRight Frame data for the "right" animation.
             * @param secondForFrameRight Duration for each frame of the "right" animation.
             */
            Drawable(std::string type, bool isAnimated, sf::Vector2f scale,
                std::vector<FrameRect> defaultFrame, float secondForDefaultFrame,
                std::vector<FrameRect> frameUP, float secondForFrameUp,
                std::vector<FrameRect> frameDown, float secondForFrameDown,
                std::vector<FrameRect> frameLeft, float secondForFrameLeft,
                std::vector<FrameRect> frameRight, float secondForFrameRight
            );

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
            std::string &getType() noexcept;

            /**
             * @brief Gets the scaling factor for the sprite.
             *
             * @return A reference to the scaling factor as an sf::Vector2f.
             */
            sf::Vector2f &getScale() noexcept;

            /**
             * @brief Checks if the sprite is animated.
             *
             * @return True if the sprite is animated, false otherwise.
             */
            const bool &getIsAnimate() const noexcept;

            /**
             * @brief Gets the texture rectangle for the sprite.
             *
             * @return The texture rectangle as an sf::IntRect.
             */
            FrameRect &getCurrentRect() noexcept;

            /**
             * @brief Gets the frame data for the default animation.
             *
             * @return A vector containing the frame indices for the default animation.
             */
            const std::vector<FrameRect> &getDefaultFrame() noexcept;

            /**
             * @brief Gets the frame data for the "up" animation.
             *
             * @return A vector containing the frame indices for the "up" animation.
             */
            const std::vector<FrameRect> &getFrameUp() noexcept;

            /**
             * @brief Gets the frame data for the "down" animation.
             *
             * @return A vector containing the frame indices for the "down" animation.
             */
            const std::vector<FrameRect> &getFrameDown() noexcept;

            /**
             * @brief Gets the frame data for the "left" animation.
             *
             * @return A vector containing the frame indices for the "left" animation.
             */
            const std::vector<FrameRect> &getFrameLeft() noexcept;

            /**
             * @brief Gets the frame data for the "right" animation.
             *
             * @return A vector containing the frame indices for the "right" animation.
             */
            const std::vector<FrameRect> &getFrameRight() noexcept;

            /**
             * @brief Gets the duration for each frame of the default animation.
             *
             * @return The duration as a float.
             */
            const float getSecondForDefaultFrame() const noexcept;

            /**
             * @brief Gets the duration for each frame of the "up" animation.
             *
             * @return The duration as a float.
             */
            const float getSecondForFrameUp() const noexcept;

            /**
             * @brief Gets the duration for each frame of the "down" animation.
             *
             * @return The duration as a float.
             */
            const float getSecondForFrameDown() const noexcept;

            /**
             * @brief Gets the duration for each frame of the "left" animation.
             *
             * @return The duration as a float.
             */
            const float getSecondForFrameLeft() const noexcept;

            /**
             * @brief Gets the duration for each frame of the "right" animation.
             *
             * @return The duration as a float.
             */
            const float getSecondForFrameRight() const noexcept;

            /**
             * @brief Gets the duration for the current animation direction.
             *
             * @return The duration as a float.
             */
            const float getSecondDependOnDirection() const noexcept;

            /**
             * @brief Sets the file path to the sprite image.
             *
             * @param newType The new file path to set.
             */
            void setType(const std::string &newType) noexcept;

            /**
             * @brief Sets the scaling factor for the sprite.
             *
             * @param newScale The new scaling factor as an sf::Vector2f.
             */
            void setScale(const sf::Vector2f &newScale) noexcept;

            /**
             * @brief Sets whether the sprite is animated.
             *
             * @param newIsAnimate True if the sprite should be animated, false otherwise.
             */
            void setIsAnimate(const bool &newIsAnimate) noexcept;

            /**
             * @brief Sets the texture rectangle for the sprite.
             *
             * @param newTextRect The new texture rectangle as an sf::IntRect.
             */
            void setCurrentRect(const FrameRect &newCurrentRect) noexcept;

            /**
             * @brief Sets the frame data for the default animation.
             *
             * @param newDefaultFrame A vector containing the new frame indices for the default animation.
             */
            void setDefaultFrame(const std::vector<FrameRect> &newDefaultFrame);

            /**
             * @brief Sets the frame data for the "up" animation.
             *
             * @param newFrameUp A vector containing the new frame indices for the "up" animation.
             */
            void setFrameUp(const std::vector<FrameRect> &newFrameUp) noexcept;

            /**
             * @brief Sets the frame data for the "down" animation.
             *
             * @param newFrameDown A vector containing the new frame indices for the "down" animation.
             */
            void setFrameDown(const std::vector<FrameRect> &newFrameDown) noexcept;

            /**
             * @brief Sets the frame data for the "left" animation.
             *
             * @param newFrameLeft A vector containing the new frame indices for the "left" animation.
             */
            void setFrameLeft(const std::vector<FrameRect> &newFrameLeft) noexcept;

            /**
             * @brief Sets the frame data for the "right" animation.
             *
             * @param newFrameRight A vector containing the new frame indices for the "right" animation.
             */
            void setFrameRight(const std::vector<FrameRect> &newFrameRight) noexcept;

            /**
             * @brief Sets the duration for each frame of the default animation.
             *
             * @param newSecondForDefaultFrame The new duration as a float.
             */
            void setSecondForDefaultFrame(const float &newSecondForDefaultFrame) noexcept;

            /**
             * @brief Sets the duration for each frame of the "up" animation.
             *
             * @param newSecondForFrameUp The new duration as a float.
             */
            void setSecondForFrameUp(const float &newSecondForFrameUp) noexcept;

            /**
             * @brief Sets the duration for each frame of the "down" animation.
             *
             * @param newSecondForFrameDown The new duration as a float.
             */
            void setSecondForFrameDown(const float &newSecondForFrameDown) noexcept;

            /**
             * @brief Sets the duration for each frame of the "left" animation.
             *
             * @param newSecondForFrameLeft The new duration as a float.
             */
            void setSecondForFrameLeft(const float &newSecondForFrameLeft) noexcept;

            /**
             * @brief Sets the duration for each frame of the "right" animation.
             *
             * @param newSecondForFrameRight The new duration as a float.
             */
            void setSecondForFrameRight(const float &newSecondForFrameRight) noexcept;

            /**
             * @brief Resets the clock and frame counter for the animation.
             */
            void resetClock() noexcept;

            /**
             * @brief Updates the frame for the animation based on the time elapsed.
             */
            void updateFrame() noexcept;
            
            /**
             * @brief Draws the sprite on the given window.
             *
             * @param window The window on which the sprite should be drawn.
             */
            void draw(sf::RenderWindow &window) noexcept;

        private:
            std::string _type; /**< The file path of the sprite image */
            bool _isAnimate; /**< Flag indicating if the sprite is animated */
            sf::Vector2f _scale; /**< Scaling factor for the sprite */
            FrameRect _currentRect; /**< Texture rectangle for the sprite */
            std::vector<FrameRect> _defaultFrame; /**< Frame data for the default (static) animation */
            std::vector<FrameRect> _frameUP; /**< Frame data for the "up" animation */
            std::vector<FrameRect> _frameDown; /**< Frame data for the "down" animation */
            std::vector<FrameRect> _frameLeft; /**< Frame data for the "left" animation */
            std::vector<FrameRect> _frameRight; /**< Frame data for the "right" animation */
            float _secondForDefaultFrame; /**< Duration for each frame of the default animation */
            float _secondForFrameUp; /**< Duration for each frame of the "up" animation */
            float _secondForFrameDown; /**< Duration for each frame of the "down" animation */
            float _secondForFrameLeft; /**< Duration for each frame of the "left" animation */
            float _secondForFrameRight; /**< Duration for each frame of the "right" animation */
            sf::Clock _clock; /**< Clock to manage frame transitions */
            int _actualFrame; /**< The current frame of animation */
            int _direction; /**< Current animation direction (up, down, left, right) */
    };
}
#endif /* !DRAWABLE_HPP_ */
