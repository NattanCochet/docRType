/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** GenerateWorld
*/

#ifndef GENERATEWORLD_HPP_
#define GENERATEWORLD_HPP_

#include <iostream>
#include <vector>
#include <functional>
#include "FastNoiseLite.hpp"
#include "Error/ErrorGenerationMap.hpp"

/**
 * @class GenerateWorld
 * @brief A class responsible for generating a world using Perlin noise.
 *
 * This class provides methods to generate 2D worlds represented as grids of values,
 * where each value is derived from Perlin noise. The generated world can be applied
 * to different types of data using a function passed as an argument.
 */
class GenerateWorld {
    public:
        /**
         * @brief Default constructor for GenerateWorld.
         *
         * Initializes any necessary data or states for world generation.
         */
        GenerateWorld();

        /**
         * @brief Destructor for GenerateWorld.
         *
         * Cleans up any resources used by the world generation process.
         */
        ~GenerateWorld();

        /**
         * @brief Generates a 2D world using Perlin noise and a user-defined function.
         *
         * This template function generates a 2D grid of values where each value is
         * computed by applying a function to a Perlin noise value. The grid size is
         * determined by the given ranges in X and Y, and the Perlin noise is generated
         * using a seed.
         *
         * @tparam VALUE The type of values in the generated world.
         * @param beginAndEndGenerationInX The start and end coordinates for generation along the X-axis.
         * @param beginAndEndGenerationInY The start and end coordinates for generation along the Y-axis.
         * @param seed The seed value for Perlin noise generation.
         * @param functionToApply A function that applies some transformation to the Perlin noise value.
         * @return A 2D vector representing the generated world with applied function values.
         * @throws ErrorGenerationMap If the provided coordinates are invalid.
         */
        template<typename VALUE>
        std::vector<std::vector<VALUE>> generateWorld(
            const std::pair<int, int> &beginAndEndGenerationInX,
            const std::pair<int, int> &beginAndEndGenerationInY,
            const std::size_t seed,
            std::function<VALUE(float)> functionToApply
        )
        {
            const int generationInX = beginAndEndGenerationInX.second - beginAndEndGenerationInX.first;
            const int generationInY = beginAndEndGenerationInY.second - beginAndEndGenerationInY.first;

            if (generationInX < 0 || generationInY < 0) {
                throw ErrorGenerationMap("Begin and End coordinates are wrong.");
            }

            const std::size_t sizeX = static_cast<std::size_t>(generationInX);
            const std::size_t sizeY = static_cast<std::size_t>(generationInY);

            std::vector<std::vector<VALUE>> result(sizeX, std::vector<VALUE>(sizeY));

            for (std::size_t i = 0; i < sizeX; ++i) {
                for (std::size_t j = 0; j < sizeY; ++j) {
                    float x = beginAndEndGenerationInX.first + static_cast<float>(i);
                    float y = beginAndEndGenerationInY.first + static_cast<float>(j);
                    float noisePerlin = this->generatePerlinValue(x, y, seed);
                    result[i][j] = functionToApply(noisePerlin);
                }
            }

            return (result);
        }

        /**
         * @brief Generates a 2D world using Perlin noise and a user-defined function for floating-point coordinates.
         *
         * This template function generates a 2D grid of values where each value is
         * computed by applying a function to a Perlin noise value. The grid size is
         * determined by the given ranges in X and Y, and the Perlin noise is generated
         * using a seed.
         *
         * @tparam VALUE The type of values in the generated world.
         * @param beginAndEndGenerationInX The start and end coordinates for generation along the X-axis.
         * @param beginAndEndGenerationInY The start and end coordinates for generation along the Y-axis.
         * @param seed The seed value for Perlin noise generation.
         * @param functionToApply A function that applies some transformation to the Perlin noise value.
         * @return A 2D vector representing the generated world with applied function values.
         * @throws ErrorGenerationMap If the provided coordinates are invalid.
         */
        template<typename VALUE>
        std::vector<std::vector<VALUE>> generateWorld(
            const std::pair<float, float> &beginAndEndGenerationInX,
            const std::pair<float, float> &beginAndEndGenerationInY,
            const std::size_t seed,
            std::function<VALUE(float)> functionToApply
        )
        {
            const float generationInX = beginAndEndGenerationInX.second - beginAndEndGenerationInX.first;
            const float generationInY = beginAndEndGenerationInY.second - beginAndEndGenerationInY.first;

            if (generationInX < 0 || generationInY < 0) {
                throw ErrorGenerationMap("Begin and End coordinates are wrong.");
            }

            const std::size_t sizeX = static_cast<std::size_t>(generationInX);
            const std::size_t sizeY = static_cast<std::size_t>(generationInY);

            std::vector<std::vector<VALUE>> result(sizeX, std::vector<VALUE>(sizeY));

            for (std::size_t i = 0; i < sizeX; ++i) {
                for (std::size_t j = 0; j < sizeY; ++j) {
                    float x = beginAndEndGenerationInX.first + static_cast<float>(i);
                    float y = beginAndEndGenerationInY.first + static_cast<float>(j);
                    float noisePerlin = this->generatePerlinValue(x, y, seed);
                    result[i][j] = functionToApply(noisePerlin);
                }
            }

            return (result);
        }

    private:
        /**
         * @brief Generates a Perlin noise value for integer coordinates.
         *
         * This method generates a Perlin noise value for the given integer coordinates.
         * The generated value is based on the provided seed.
         *
         * @param x The x-coordinate for the Perlin noise.
         * @param y The y-coordinate for the Perlin noise.
         * @param seed The seed for the Perlin noise generation.
         * @return The generated Perlin noise value.
         */
        float generatePerlinValue(int x, int y, std::size_t seed);

        /**
         * @brief Generates a Perlin noise value for floating-point coordinates.
         *
         * This method generates a Perlin noise value for the given floating-point coordinates.
         * The generated value is based on the provided seed.
         *
         * @param x The x-coordinate for the Perlin noise.
         * @param y The y-coordinate for the Perlin noise.
         * @param seed The seed for the Perlin noise generation.
         * @return The generated Perlin noise value.
         */
        float generatePerlinValue(float x, float y, std::size_t seed);
};

#endif /* !GENERATEWORLD_HPP_ */
