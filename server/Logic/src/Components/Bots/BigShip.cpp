/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** BigShip
*/

#include "../../../include/Components/Bots/BigShip.hpp"

BigShip::BigShip(float delay, float delay2, float delay3)
{
    _delay = delay;
    _delay2 = delay2;
    _delay3 = delay3;
}

BigShip::~BigShip()
{
}

void BigShip::shootProjectile(World &world, std::size_t myIndexEntity)
{
    CreateEntity &ce = world.getClassCreateEntity();
    std::optional<Position> &pos = world.getRegistry().get_components<Position>()[myIndexEntity];
    std::optional<Velocity> &vel = world.getRegistry().get_components<Velocity>()[myIndexEntity];

    int speed_thing = 1;

    sf::Vector2f coordsAct = pos->getPosition();
        ce.createLaserBoss(sf::Vector2f(coordsAct.x, coordsAct.y + 10), world.getRegistry(), myIndexEntity, 30, sf::Vector2i(-20, -10), Vector<int, 2>(30, 10));

    if (_bigLaserClock.getElapsedTime().asSeconds() >= _delay2) {
        ce.createLaserBoss(sf::Vector2f(coordsAct.x, coordsAct.y + 400), world.getRegistry(), myIndexEntity, 60, sf::Vector2i(-20, 0), Vector<int, 2>(150, 20));
        _bigLaserClock.restart();
    }

    if (vel->getSpeed().y < 0) {
        speed_thing *= -1;
    }

    if (_backLasersClock.getElapsedTime().asSeconds() >= _delay3) {
        ce.createLaserBoss(sf::Vector2f(coordsAct.x + 750, coordsAct.y + 100), world.getRegistry(), myIndexEntity, 20, sf::Vector2i(5, -4 * speed_thing), Vector<int, 2>(30, 10));
        ce.createLaserBoss(sf::Vector2f(coordsAct.x + 750, coordsAct.y + 100), world.getRegistry(), myIndexEntity, 20, sf::Vector2i(5, 0), Vector<int, 2>(30, 10));
        ce.createLaserBoss(sf::Vector2f(coordsAct.x + 750, coordsAct.y + 100), world.getRegistry(), myIndexEntity, 20, sf::Vector2i(5, 4 * speed_thing), Vector<int, 2>(30, 10));
        _backLasersClock.restart();
    }
}

void BigShip::moveBot(World &world, std::size_t myIndexEntity)
{
    std::optional<Position> &pos = world.getRegistry().get_components<Position>()[myIndexEntity];
    std::optional<Velocity> &vel = world.getRegistry().get_components<Velocity>()[myIndexEntity];

    sf::Vector2f coordsAct = pos->getPosition();

    if (coordsAct.x <= 10 || coordsAct.x >= 1300 || coordsAct.y <= 10 || coordsAct.y >= 1070) {
        vel->setSpeed(vel->getSpeed().x * -1, vel->getSpeed().y * -1);
    }

}