/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** PlayerAISystem
*/

#include "../../include/Systems.hpp"

int Systems::PlayerAISystem(World &world, NetworkServer &networkserver)
{
    Registry &r = world.getRegistry();

    ComponentArray<PlayerAI> &ais = r.get_components<PlayerAI>();
    ComponentArray<Controllable> &controllables = r.get_components<Controllable>();

    std::size_t index = 0;

    auto areOpposites = [](const std::string &dir1, const std::string &dir2) {
        return (dir1 == "left" && dir2 == "right") || (dir1 == "right" && dir2 == "left") ||
               (dir1 == "up" && dir2 == "down") || (dir1 == "down" && dir2 == "up");
    };

    for (std::optional<PlayerAI> &a : ais) {
        if (a && a.has_value() && index < controllables.size() && controllables[index].has_value()) {
            std::optional<Controllable> &c = controllables[index];
            VirtualKeyBoard &kb = c->getVirtualKeyboard();
            kb.changeValueKeyboard(VirtualKeyBoard::CONTROL::SHOOT, true);
            if (a->getMoveClock().getElapsedTime().asSeconds() >= a->getDelay()) {
                kb.changeValueKeyboard(VirtualKeyBoard::CONTROL::LEFT, false);
                kb.changeValueKeyboard(VirtualKeyBoard::CONTROL::RIGHT, false);
                kb.changeValueKeyboard(VirtualKeyBoard::CONTROL::UP, false);
                kb.changeValueKeyboard(VirtualKeyBoard::CONTROL::DOWN, false);
                std::vector<std::string> values = {"left", "right", "up", "down"};

                std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)) + index);
                std::shuffle(values.begin(), values.end(), rng);

                std::vector<std::string> selected;
                for (const auto &dir : values) {
                    if (selected.empty() || !areOpposites(selected[0], dir)) {
                        selected.push_back(dir);
                    }
                    if (selected.size() == 2)
                        break;
                }

                for (const auto &dir : selected) {
                    if (dir == "left")
                        kb.changeValueKeyboard(VirtualKeyBoard::CONTROL::LEFT, true);
                    else if (dir == "right")
                        kb.changeValueKeyboard(VirtualKeyBoard::CONTROL::RIGHT, true);
                    else if (dir == "up")
                        kb.changeValueKeyboard(VirtualKeyBoard::CONTROL::UP, true);
                    else if (dir == "down")
                        kb.changeValueKeyboard(VirtualKeyBoard::CONTROL::DOWN, true);
                }
                a->getMoveClock().restart();
            }
            if (a->getShootClock().getElapsedTime().asSeconds() >= a->getShootDelay() && a->getStacks() <= 8) {
                kb.changeValueKeyboard(VirtualKeyBoard::CONTROL::SHOOT, false);
                a->getShootClock().restart();
                a->setStacks(a->getStacks() + 1);
            }
            if (a->getBigShoot().getElapsedTime().asSeconds() >= a->getBigShootDelay() && a->getStacks() >= 8) {
                kb.changeValueKeyboard(VirtualKeyBoard::CONTROL::SHOOT, false);
                a->setStacks(0);
                a->getBigShoot().restart();
            }
        }
        index++;
    }
    return 0;
}
