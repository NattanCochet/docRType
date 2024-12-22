/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Assets
*/

#pragma once
#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "../Error/ErrorKeyNotFound.hpp"

#ifndef ASSETS_HPP_
#define ASSETS_HPP_

/**
 * @class Assets
 * @brief Manages loading and accessing game assets like sprites.
 *
 * This class allows for loading sprites from files and storing them in a map.
 */
class Assets {
    public:
        /**
         * @brief Default constructor for Assets.
         */
        Assets();

        /**
         * @brief Destructor for Assets.
         *
         * Cleans up any loaded assets.
         */
        ~Assets();

        /**
         * @brief Loads a sprite into the assets container.
         *
         * This function loads a sprite from a file and stores it in the asset list.
         * @param filePath The path to the sprite image file.
         * @param dimensions The dimensions of the sprite to load (e.g., width, height).
         */
        void LoadSprite(std::string filePath, std::vector<int> dimensions);

        /**
         * @brief Retrieves a sprite from the asset container.
         *
         * This function returns a sprite that has been previously loaded.
         * @param filePath The path to the sprite image file.
         * @return The sprite corresponding to the given file path.
         * @throws ErrorKeyNotFound If the sprite cannot be found in the asset list.
         */
        sf::Sprite getSprite(std::string filePath);

    private:
        /**
         * @brief A map that stores loaded sprites by their file paths.
         *
         * This map associates sprite file paths with their respective sf::Sprite objects.
         */
        std::map<std::string, sf::Sprite> _list;

};

#endif /* !ASSETS_HPP_ */
