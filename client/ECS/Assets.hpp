/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Assets
*/

/**
 * @file Assets.hpp
 * @brief Header file for the Assets class, responsible for loading and managing graphical assets.
 */

#pragma once
#include "../Error/Error.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

#ifndef ASSETS_HPP_
#define ASSETS_HPP_

#ifdef _WIN32
#define PATH "../../" ///< Path definition for Windows systems
#else
#define PATH "../" ///< Path definition for non-Windows systems
#endif

/**
 * @class Assets
 * @brief Class to load and manage sprites, text, and rectangles.
 *
 * This class handles the loading of different graphical assets (sprites, texts, rectangles)
 * and provides access methods to retrieve them based on their file paths or names.
 */
class Assets
{
  public:
    /**
     * @brief Default constructor for the Assets class.
     * Initializes the internal maps for storing loaded assets.
     */
    Assets();

    /**
     * @brief Destructor for the Assets class.
     * Cleans up any dynamically allocated resources.
     */
    ~Assets();

    /**
     * @brief Loads a sprite from a file path with the specified rectangle area.
     * @param filepath The path to the sprite file.
     * @param rect The rectangle defining the area to be used from the sprite.
     */
    void loadSprite(std::string filepath, sf::IntRect rect, std::string name, sf::Vector2f scale);

    /**
     * @brief Loads text from a file path.
     * @param filepath The path to the text file.
     */
    void loadText(std::string filepath, std::string name);

    /**
     * @brief Loads a default rectangle shape.
     * Initializes a basic rectangle shape for later use.
     */
    void loadRectangle();

    /**
     * @brief Retrieves a sprite from the loaded assets based on its file path.
     * @param filePath The path to the sprite file.
     * @return A pointer to the corresponding `sf::Sprite` object.
     */
    sf::Sprite *getSprite(std::string name);

    /**
     * @brief Retrieves text from the loaded assets based on its file path.
     * @param filePath The path to the text file.
     * @return A pointer to the corresponding `sf::Text` object.
     */
    sf::Text *getText(std::string name);

    /**
     * @brief Retrieves a rectangle shape from the loaded assets based on its name.
     * @param name The name of the rectangle shape.
     * @return A pointer to the corresponding `sf::RectangleShape` object.
     */
    sf::RectangleShape *getRectangle(std::string name);

  private:
    std::map<std::string, sf::Sprite> _mapSprites;           ///< Map of loaded sprites, indexed by file path.
    std::map<std::string, sf::Text> _mapTexts;               ///< Map of loaded texts, indexed by file path.
    std::map<std::string, sf::RectangleShape> _mapRectangle; ///< Map of loaded rectangles, indexed by name.
};

#endif /* !ASSETS_HPP_ */
