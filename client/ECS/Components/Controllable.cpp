/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** Controllable
*/

#include "Controllable.hpp"

Controllable::Controllable()
{
    _keys[CONTROL::SHOOT] = false;
    _keys[CONTROL::FORCE] = false;
    _keys[CONTROL::UP] = false;
    _keys[CONTROL::DOWN] = false;
    _keys[CONTROL::LEFT] = false;
    _keys[CONTROL::RIGHT] = false;
}

Controllable::~Controllable()
{
}

void Controllable::updateControl(World &world, sf::Keyboard::Key key, bool pressed, std::size_t index, Network *network)
{
    for (auto it = world._controlsMap.begin(); it != world._controlsMap.end(); it++) {
        if (it->second == key) {
            if (_keys.find(it->first) != _keys.end() && _keys[it->first] != pressed) {
                _keys[it->first] = pressed;
                network->sendKeyboard(world.getClient(), _keys[it->first], it->first);
            }
        }
    }
}

void Controllable::changePosition(Position &pos)
{
    sf::Vector2f posV = pos.getPosition();
    if (_keys[CONTROL::UP]) {
        posV.y -= 15;
        if (posV.y < 0) {
            posV.y = 0;
        }
    }
    if (_keys[CONTROL::DOWN]) {
        posV.y += 15;
        if (posV.y > 1080) {
            posV.y = 1080;
        }
    }
    if (_keys[CONTROL::LEFT]) {
        posV.x -= 15;
        if (posV.x < 0) {
            posV.x = 0;
        }
    }
    if (_keys[CONTROL::RIGHT]) {
        posV.x += 15;
        if (posV.x > 1920) {
            posV.x = 1920;
        }
    }
    pos.setPosition(posV);
}