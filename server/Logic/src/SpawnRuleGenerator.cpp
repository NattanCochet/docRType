/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** SpawnRuleGenerator
*/

#include "../include/SpawnRuleGenerator.hpp"

SpawnRule::Generator::Generator()
{
}

SpawnRule::Generator::~Generator()
{
}

void SpawnRule::Generator::addEntity(const EntityType &newEntity)
{
    _entities.push_back(newEntity);
}

void SpawnRule::Generator::addEntity(std::size_t id, float baseThreshold, float levelScaling,
    float maxThresholdBonus, std::size_t sizeEntity, int scoreByDeath, std::size_t minLevel)
{
    _entities.push_back({id, baseThreshold, levelScaling, maxThresholdBonus, minLevel, sizeEntity, scoreByDeath});
    _entities.sort([](const SpawnRule::EntityType &a, const SpawnRule::EntityType &b) {
        return (a.baseThreshold < b.baseThreshold);
    });
}

std::function<SpawnRule::Generator::ENTITIES(float)> SpawnRule::Generator::createFunctionForRuleWithEnum(const std::size_t &level)
{
    return [this, level](float perlinNoise) -> SpawnRule::Generator::ENTITIES {
        float currentThreshold = -1.0f;

        for (const auto& entity : _entities) {
            if (level >= entity.minLevel) {
                float levelBonus = std::min(entity.maxThresholdBonus,
                                            level * entity.levelScaling);
                float nextThreshold = currentThreshold +
                                    entity.baseThreshold + levelBonus;

                nextThreshold = std::min(nextThreshold, 1.0f);

                if (perlinNoise < nextThreshold) {
                    return static_cast<SpawnRule::Generator::ENTITIES>(entity.id);
                }

                currentThreshold = nextThreshold;
            }
        }

        return SpawnRule::Generator::ENTITIES::NOTHING;
    };
}

std::function<int(float)> SpawnRule::Generator::createFunctionForRuleWithID(const std::size_t &level)
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

SpawnRule::EntityType &SpawnRule::Generator::getEntity(std::size_t id)
{
    for (SpawnRule::EntityType &entity : _entities) {
        if (entity.id == id) {
            return (entity);
        }
    }
    throw ErrorKeyNotFound(std::to_string(id), "SpawnRuleGenerator::getEntity");
}

std::size_t SpawnRule::Generator::getSizeEntity(std::size_t id)
{
    for (SpawnRule::EntityType &entity : _entities) {
        if (entity.id == id) {
            return (entity.sizeEntity);
        }
    }
    throw ErrorKeyNotFound(std::to_string(id), "SpawnRuleGenerator::getSizeEntity");
}

bool SpawnRule::Generator::hasEnoughtPlaceForEnemy(std::vector<std::vector<int>> &world, std::size_t y, std::size_t x, std::size_t sizeEntity)
{
    if (y + sizeEntity > world.size() || x + sizeEntity > world[0].size())
       return (false);

    const int entityID = world[y][x];

    for (std::size_t i = 0; i < sizeEntity; i++) {
        for (std::size_t j = 0; j < sizeEntity; j++) {
            if (world[y + i][x + j] != entityID)
                return (false);
        }
    }
    for (std::size_t i = 0; i < sizeEntity; i++) {
        std::fill(world[y + i].begin() + x, world[y + i].begin() + x + sizeEntity, 0);
    }
    return (true);
}
