/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** GenerateWorld
*/

#include "../include/GenerateWorld.hpp"

GenerateWorld::GenerateWorld()
{
}

GenerateWorld::~GenerateWorld()
{
}

float GenerateWorld::generatePerlinValue(int x, int y, std::size_t seed)
{
    FastNoiseLite noise;

    noise.SetSeed(seed);
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFrequency(1.0f / 50.0f);
    noise.SetFractalOctaves(4);
    return noise.GetNoise((float)x, (float)y);
}

float GenerateWorld::generatePerlinValue(float x, float y, std::size_t seed)
{
    FastNoiseLite noise;

    noise.SetSeed(seed);
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFrequency(1.0f / 50.0f);
    noise.SetFractalOctaves(4);
    return noise.GetNoise(x, y);
}
