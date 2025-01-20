/*
** EPITECH PROJECT, 2024
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** ClickableSystem
*/

#include "../Systems.hpp"

int Systems::clickableSystem(World &world, Network *network)
{
    Registry &r = world.getRegistry();
    Registry &rOnline = world.getOnlineRegistry();
    sf::RenderWindow *window = world.getWindow();
    ComponentArray<Position> &position = r.get_components<Position>();
    ComponentArray<Drawable> &drawables = r.get_components<Drawable>();
    ComponentArray<Clickable> &clickables = r.get_components<Clickable>();
    ComponentArray<Position> &positionOnline = rOnline.get_components<Position>();
    ComponentArray<Drawable> &drawablesOnline = rOnline.get_components<Drawable>();
    ComponentArray<Clickable> &clickablesOnline = rOnline.get_components<Clickable>();
    std::vector<std::pair<World::PRESS, sf::Vector2i>> mouseActions = world.getMouseAction();
    std::size_t index = 0;

    for (std::optional<Clickable> &clickable : clickables) {
        if (clickable && clickable.has_value() && position[index] && position[index].has_value() && drawables[index] &&
            drawables[index].has_value()) {
            for (std::vector<std::pair<World::PRESS, sf::Vector2i>>::iterator it = mouseActions.begin();
                 it != mouseActions.end(); it++) {
                sf::Vector2f pos = position[index]->getPosition();
                sf::Vector2f size = drawables[index]->getSizeRectangle();
                // std::cout << index  << " pos " << size.x << "," << size.y << std::endl;
                if (it->second.x >= pos.x - (size.x / 2) && it->second.x <= pos.x + (size.x / 2) &&
                    it->second.y >= pos.y - (size.y / 2) && it->second.y <= pos.y + (size.y / 2))
                    clickable->getAction()(index);
            }
        }
        index++;
    }
    index = 0;
    for (std::optional<Clickable> &clickable : clickablesOnline) {
        if (clickable && clickable.has_value() && positionOnline[index] && positionOnline[index].has_value() &&
            drawablesOnline[index] && drawablesOnline[index].has_value()) {
            for (std::vector<std::pair<World::PRESS, sf::Vector2i>>::iterator it = mouseActions.begin();
                 it != mouseActions.end(); it++) {
                sf::Vector2f pos = positionOnline[index]->getPosition();
                sf::Vector2f size = drawablesOnline[index]->getSizeRectangle();
                // std::cout << index  << " pos " << size.x << "," << size.y << std::endl;
                if (it->second.x >= pos.x - (size.x / 2) && it->second.x <= pos.x + (size.x / 2) &&
                    it->second.y >= pos.y - (size.y / 2) && it->second.y <= pos.y + (size.y / 2))
                    clickable->getAction()(index);
            }
        }
        index++;
    }
    return 0;
}
