/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** SpatialDustman
*/

#include "../../../include/Components/Bots/SpatialDustman.hpp"

SpatialDustman::SpatialDustman(float delay, float column1, float column2, float column3, float column4)
{
    _delay = delay;
    _column1 = column1;
    _column2 = column2;
    _column3 = column3;
    _column4 = column4;
}

SpatialDustman::~SpatialDustman()
{
}

void SpatialDustman::shootProjectile(World &world, std::size_t myIndexEntity)
{
    CreateEntity &ce = world.getClassCreateEntity();
    std::optional<Position> &pos = world.getRegistry().get_components<Position>()[myIndexEntity];
    std::optional<Drawable::Drawable> &drawables = world.getRegistry().get_components<Drawable::Drawable>()[myIndexEntity];

    if (drawables->getCurrentFrame() == 3)
    {
        ce.createLaser(sf::Vector2f(pos->getPosition().x - 30, pos->getPosition().y + 120), world.getRegistry(), myIndexEntity, false, false);
    }

    std::vector<sf::Vector2f> columnPositions = {
        {600, 0}, {750, 0}, {900, 0}, {1050, 0}, {1200, 0}, {1350, 0}, {1400, 0}, {1500, 0}, {1650, 0}};

    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution<int> columnDist(0, int(columnPositions.size()));
    static std::uniform_real_distribution<float> timeDist(1.0f, 5.0f);

    static std::vector<float> timers = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    static std::vector<float> thresholds = {
        timeDist(rng), timeDist(rng), timeDist(rng),
        timeDist(rng), timeDist(rng), timeDist(rng),
        timeDist(rng), timeDist(rng)
    };

    float elapsedTime = _clock.getElapsedTime().asSeconds();

    for (int i = 0; i < columnPositions.size() - 1; ++i)
    {
        timers[i] += elapsedTime;
        if (timers[i] > thresholds[i])
        {
            ce.createBossBomb(columnPositions[i], world.getRegistry(), myIndexEntity);
            timers[i] = 0.0f;
            thresholds[i] = timeDist(rng);
        }
    }
    _clock.restart();
}