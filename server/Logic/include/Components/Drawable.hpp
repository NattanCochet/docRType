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
#include "../Error/ErrorNoObject.hpp"

namespace Drawable
{
    class FrameRect
    {
        public:
            FrameRect(int rectLeft, int rectTop, int rectWidth, int rectHeight);

            ~FrameRect() = default;

        public:
            int _rectLeft;
            int _rectTop;
            int _rectWidth;
            int _rectHeight;
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
             * @brief Gets the frame data for the "up" animation.
             *
             * @return A vector containing the frame indices for the "up" animation.
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

            const float getSecondForDefaultFrame() const noexcept;
            const float getSecondForFrameUp() const noexcept;
            const float getSecondForFrameDown() const noexcept;
            const float getSecondForFrameLeft() const noexcept;
            const float getSecondForFrameRight() const noexcept;

            const float getSecondDependOnDirection() const noexcept;

            /**
             * @brief Sets the file path to the sprite image.
             *
             * @param newPath The new file path to set.
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
             * @brief Sets the frame data for the "up" animation.
             *
             * @param newFrameUp A vector containing the new frame indices for the "up" animation.
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

            void setSecondForDefaultFrame(const float &newSecondForDefaultFrame) noexcept;
            void setSecondForFrameUp(const float &newSecondForFrameUp) noexcept;
            void setSecondForFrameDown(const float &newSecondForFrameDown) noexcept;
            void setSecondForFrameLeft(const float &newSecondForFrameLeft) noexcept;
            void setSecondForFrameRight(const float &newSecondForFrameRight) noexcept;

            void passNextFrame() noexcept;
            void setDirectionFrame(const int &direction) noexcept;

            sf::Clock &getClock() noexcept;

            std::size_t getCurrentFrame() const;

        protected:
        private:
            /**
             * @brief The file path to the sprite image.
             *
             * This private member stores the file path for the image (sprite sheet) used to draw the sprite.
             */
            std::string _type;

            /**
             * @brief A flag indicating if the sprite is animated.
             *
             * This private member determines whether the sprite should be animated.
             */
            bool _isAnimated;

            /**
             * @brief The scale factor for the sprite.
             *
             * This private member defines how much to scale the sprite when rendering.
             */
            sf::Vector2f _scale;

            /**
             * @brief Frame data for the "up" animation.
             *
             * This private member stores the frame indices for the "up" animation.
             */
            std::vector<FrameRect> _defaultFrame;

            /**
             * @brief Frame data for the "down" animation.
             *
             * This private member stores the frame indices for the "down" animation.
             */
            std::vector<FrameRect> _frameUP;

            /**
             * @brief Frame data for the "left" animation.
             *
             * This private member stores the frame indices for the "left" animation.
             */
            std::vector<FrameRect> _frameDown;

            /**
             * @brief Frame data for the "right" animation.
             *
             * This private member stores the frame indices for the "right" animation.
             */
            std::vector<FrameRect> _frameLeft;

            /**
             * @brief Frame data for the "right" animation.
             *
             * This private member stores the frame indices for the "right" animation.
             */
            std::vector<FrameRect> _frameRight;

            /**
             * @brief The current frame of the animation.
             *
             * This private member keeps track of the current animation frame.
             */
            std::size_t _currentFrame;

            int _directionFrame;

            float _secondForDefaultFrame;
            float _secondForFrameUp;
            float _secondForFrameDown;
            float _secondForFrameLeft;
            float _secondForFrameRight;

            sf::Clock _clock;
    };
};

#endif /* !DRAWABLE_HPP_ */