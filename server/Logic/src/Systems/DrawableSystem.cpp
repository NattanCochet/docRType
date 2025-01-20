/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** DrawableSystem
*/

#include "../../include/Systems.hpp"

int Systems::drawableSystem(World &world, NetworkServer &server)
{
    Registry &r = world.getRegistry();

    ComponentArray<Drawable::Drawable> &drawables = r.get_components<Drawable::Drawable>();
    ComponentArray<Controllable> &controllables = r.get_components<Controllable>();

    std::size_t index = 0;

    for (std::optional<Drawable::Drawable> &drawable : drawables) {
        if (!drawable || !drawable.has_value() || !drawable->getIsAnimate()) {
            index += 1;
            continue;
        }
        if (index < controllables.size() && controllables[index] && controllables[index].has_value()) {
            VirtualKeyBoard &keyBoard = controllables[index]->getVirtualKeyboard();
            const auto [x_axis, y_axis] = getDirectionControllable(keyBoard);
            if (x_axis == 0 && y_axis == 0) {
                drawable->setDirectionFrame(0);
            } else if (y_axis == 1) {
                drawable->setDirectionFrame(3);
            } else if (y_axis == -1) {
                drawable->setDirectionFrame(1);
            } else if (x_axis == 1) {
                drawable->setDirectionFrame(2);
            } else if (x_axis == -1) {
                drawable->setDirectionFrame(4);
            }
        } else {
            drawable->setDirectionFrame(0);
        }
        sf::Clock &clock = drawable->getClock();
        if (clock.getElapsedTime().asSeconds() >= drawable->getSecondDependOnDirection()) {
            drawable->passNextFrame();
            clock.restart();
        }
        index += 1;
    }
    return (0);
}

const std::pair<int, int> Systems::getDirectionControllable(VirtualKeyBoard &keyBoard)
{
    int x = 0;
    int y = 0;

    if (keyBoard.isKeyIsPressed(VirtualKeyBoard::CONTROL::UP)) {
        y -= 1;
    }
    if (keyBoard.isKeyIsPressed(VirtualKeyBoard::CONTROL::DOWN)) {
        y += 1;
    }
    if (keyBoard.isKeyIsPressed(VirtualKeyBoard::CONTROL::LEFT)) {
        x -= 1;
    }
    if (keyBoard.isKeyIsPressed(VirtualKeyBoard::CONTROL::RIGHT)) {
        x += 1;
    }
    return (std::make_pair(x, y));
}

/*
Registry &r = world.getRegistry();

    ComponentArray<Drawable> &drawable = r.get_components<Drawable>();
    ComponentArray<Position> &position = r.get_components<Position>();
    ComponentArray<Controllable> &controllable = r.get_components<Controllable>();
    ComponentArray<Velocity> &velocity = r.get_components<Velocity>();

    static std::unordered_map<std::size_t, std::size_t> frameIndexMap;
    std::size_t index = 0;

    for (auto &d : drawable) {
        if (velocity.size() == 0) {
            d->setTextRect(sf::IntRect(0 * d->getRect()[0], 0, d->getRect()[0], d->getRect()[1]));
        } else if (d && d.has_value() && controllable.size() > 0) {
            if (controllable.size() > index && controllable[index] && controllable[index].has_value()) {
                std::vector<int> frames;
                VirtualKeyBoard &keyboard = world.getVirtualKeyBoardFromClientID(controllable[index]->getClientID());
                if (keyboard.isKeyIsPressed(VirtualKeyBoard::UP) && !keyboard.isKeyIsPressed(VirtualKeyBoard::DOWN)) {
                    frames = d->getFrameDown();
                } else if (!keyboard.isKeyIsPressed(VirtualKeyBoard::UP) && keyboard.isKeyIsPressed(VirtualKeyBoard::DOWN)) {
                   frames = d->getFrameUp();
                }
                if (world.getClock().getElapsedTime().asSeconds() > d->getRect()[3] && frames.size() != 0) {
                    int currentFrame = frames[frameIndexMap[index]];
                    d->setTextRect(sf::IntRect(currentFrame * d->getRect()[0], 0, d->getRect()[0], d->getRect()[1]));
                    frameIndexMap[index] = (frameIndexMap[index] + 1) % frames.size();
                    world.getClock().restart();
                }
            }
        } else if (d && d.has_value() && velocity[index] && velocity[index].has_value() && d->getIsAnimate()) {
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
            if (!frames.empty()) {
                if (frameIndexMap.find(index) == frameIndexMap.end()) {
                    frameIndexMap[index] = 0;
                }
                if (world.getClock().getElapsedTime().asSeconds() > d->getRect()[3]) {
                    int currentFrame = frames[frameIndexMap[index]];
                    d->setTextRect(sf::IntRect(currentFrame * d->getRect()[0], 0, d->getRect()[0], d->getRect()[1]));
                    frameIndexMap[index] = (frameIndexMap[index] + 1) % frames.size();
                    world.getClock().restart();
                }
            }
        }
        index++;
    }
    return 0;*/
