/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** SpawnRuleGenerator
*/

#include "../include/SpawnRuleGenerator.hpp"

SpawnRuleGenerator::SpawnRuleGenerator()
{
}

SpawnRuleGenerator::~SpawnRuleGenerator()
{
}

void SpawnRuleGenerator::addEntity(const EntityType &newEntity)
{
    _entities.push_back(newEntity);
}

void SpawnRuleGenerator::addEntity(std::size_t id, float baseThreshold, float levelScaling,
    float maxThresholdBonus, std::size_t minLevel)
{
    _entities.push_back({id, baseThreshold, levelScaling, maxThresholdBonus, minLevel});
}

std::function<SpawnRuleGenerator::ENTITIES(float)> SpawnRuleGenerator::createFunctionForRuleWithEnum(const std::size_t &level)
{
    return [this, level](float perlinNoise) -> SpawnRuleGenerator::ENTITIES {
        float currentThreshold = -1.0f;

        for (const auto& entity : _entities) {
            if (level >= entity.minLevel) {
                float levelBonus = std::min(entity.maxThresholdBonus,
                                            level * entity.levelScaling);
                float nextThreshold = currentThreshold +
                                    entity.baseThreshold + levelBonus;

                nextThreshold = std::min(nextThreshold, 1.0f);

                if (perlinNoise < nextThreshold) {
                    return static_cast<SpawnRuleGenerator::ENTITIES>(entity.id);
                }

                currentThreshold = nextThreshold;
            }
        }

        return SpawnRuleGenerator::ENTITIES::NOTHING;
    };
}

std::function<int(float)> SpawnRuleGenerator::createFunctionForRuleWithID(const std::size_t &level)
{
    return [this, level](float perlinNoise) -> int {
        float currentThreshold = -1.0f;

        for (const auto& entity : _entities) {
            if (level >= entity.minLevel) {
                float levelBonus = std::min(entity.maxThresholdBonus,
                                            level * entity.levelScaling);
                float nextThreshold = currentThreshold +
                                    entity.baseThreshold + levelBonus;

                nextThreshold = std::min(nextThreshold, 1.0f);

                if (perlinNoise < nextThreshold) {
                    return entity.id;
                }

                currentThreshold = nextThreshold;
            }
        }

        return 0;
    };
}
