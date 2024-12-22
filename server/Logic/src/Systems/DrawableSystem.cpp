/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** DrawableSystem
*/

#include "../../include/Systems.hpp"

int Systems::drawableSystem(World &world)
{
    Registry &r = world.getRegistry();

    ComponentArray<Drawable> &drawable = r.get_components<Drawable>();
    ComponentArray<Position> &position = r.get_components<Position>();
    ComponentArray<Controllable> &controllable = r.get_components<Controllable>();
    ComponentArray<Velocity> &velocity = r.get_components<Velocity>();

    static std::unordered_map<std::size_t, std::size_t> frameIndexMap;
    std::size_t index = 0;

    for (auto &d : drawable) {
        if (d && d.has_value() && controllable.size() > 0) {
            if (controllable[index] && controllable[index].has_value()) {
                std::vector<int> frames;
                VirtualKeyBoard &keyboard = world.getVirtualKeyBoardFromClientID(controllable[index]->getClientID());
                if (keyboard.isKeyIsPressed(VirtualKeyBoard::UP) && !keyboard.isKeyIsPressed(VirtualKeyBoard::DOWN)) {
                    frames = d->getFrameDown();
                } else if (!keyboard.isKeyIsPressed(VirtualKeyBoard::UP) && keyboard.isKeyIsPressed(VirtualKeyBoard::DOWN)) {
                   frames = d->getFrameUp();
                }
                if (world.getClock().getElapsedTime().asSeconds() > d->getRect()[3]) {
                    int currentFrame = frames[frameIndexMap[index]];
                    d->setTextRect(sf::IntRect(currentFrame * d->getRect()[0], 0, d->getRect()[0], d->getRect()[1]));
                    frameIndexMap[index] = (frameIndexMap[index] + 1) % frames.size();
                    world.getClock().restart();
                }
            }
        }
        else if (d && d.has_value() && velocity[index] && velocity[index].has_value() && d->getIsAnimate()) {
            std::vector<int> frames;
            if (velocity[index]->getSpeed().x > 0) {
                frames = d->getFrameRight();
            } else if (velocity[index]->getSpeed().x < 0) {
                frames = d->getFrameLeft();
            } else if (velocity[index]->getSpeed().y > 0) {
                frames = d->getFrameDown();
            } else {
                frames = d->getFrameUp();
            }
            if (frameIndexMap.find(index) == frameIndexMap.end()) {
                frameIndexMap[index] = frames[0];
            }
            if (world.getClock().getElapsedTime().asSeconds() > d->getRect()[3]) {
                int currentFrame = frames[frameIndexMap[index]];
                d->setTextRect(sf::IntRect(currentFrame * d->getRect()[0], 0, d->getRect()[0], d->getRect()[1]));
                frameIndexMap[index] = (frameIndexMap[index] + 1) % frames.size();
                world.getClock().restart();
            }
        }
        index++;
    }

    return 0;
}