/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ControllableSystem
*/

#include "../Systems.hpp"

int Systems::controllableSystem(World &world, Network *network)
{
    Registry &r = world.getRegistry();
    ComponentArray<Position> &positions = r.get_components<Position>();
    ComponentArray<Controllable> &controls = r.get_components<Controllable>();
    Registry &rOnline = world.getOnlineRegistry();
    ComponentArray<Position> &positionsOnline = rOnline.get_components<Position>();
    ComponentArray<Controllable> &controlsOnline = rOnline.get_components<Controllable>();

    std::size_t index = 0;

    for (std::optional<Controllable> &control : controls) {
        if (control && control.has_value()) {
            std::vector<std::pair<World::PRESS, sf::Keyboard::Key>> keyActions = world.getKeyActions();
            for (auto it = keyActions.begin(); it != keyActions.end(); it++) {
                control->updateControl(world, it->second, it->first == World::PRESSED, index, network);
            }
            if (positions[index] && positions[index].has_value()) {
                control->changePosition(*positions[index]);
            }
        }
        index++;
    }
    index = 0;
    for (std::optional<Controllable> &control : controlsOnline) {
        if (control && control.has_value()) {
            std::vector<std::pair<World::PRESS, sf::Keyboard::Key>> keyActions = world.getKeyActions();
            for (auto it = keyActions.begin(); it != keyActions.end(); it++) {
                control->updateControl(world, it->second, it->first == World::PRESSED, index, network);
            }
            if (positionsOnline[index] && positionsOnline[index].has_value()) {
                control->changePosition(*positionsOnline[index]);
            }
        }
        index++;
    }
    world.clearKeyAction();
    return 0;
}
