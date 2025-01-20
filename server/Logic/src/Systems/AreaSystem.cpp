/*
** EPITECH PROJECT, 2025
** B-CPP-500-MAR-5-2-rtype-tom.calogheris
** File description:
** AreaSystem
*/

#include "../../include/Systems.hpp"

int Systems::areaSystem(World &world, NetworkServer &server)
{
    Registry &r = world.getRegistry();

    ComponentArray<Area> &areas = r.get_components<Area>();
    ComponentArray<Position> &positions = r.get_components<Position>();
    ComponentArray<Drawable::Drawable> &drawables = r.get_components<Drawable::Drawable>();

    std::size_t index = 0;

    for (std::optional<Area> &area : areas) {
        if (!area.has_value() || index >= positions.size() || !positions[index].has_value() ||
            index >= drawables.size() || !drawables[index].has_value()) {
            index += 1;
            continue;
        }
        const Drawable::FrameRect &rect = drawables[index]->getCurrentRect();
        const sf::Vector2f &scale = drawables[index]->getScale();
        Vector<int, 2> &positionArea = area->getPosition();
        const sf::Vector2f &position = positions[index]->getPosition();
        positionArea[0] = position.x + ((rect._rectWidth * scale.x) / 2) - area->getRadius();
        positionArea[1] = position.y + ((rect._rectHeight * scale.y) / 2) - area->getRadius();

        area->clearData();
        calculateArea(areas, index);
        index += 1;
    }
    return (0);
}

void Systems::calculateArea(ComponentArray<Area> &areas, const std::size_t &indexArea)
{
    std::size_t index = 0;

    Area &areaToCalculate = areas[indexArea].value();
    const Vector<int, 2> &posDefaultArea = areaToCalculate.getPosition();

    for (std::optional<Area> &area : areas) {
        if (index == indexArea || !area.has_value()) {
            index += 1;
            continue;
        }
        const Vector<int, 2> &posOtherArea = area->getPosition();
        int dx = posOtherArea[0] - posDefaultArea[0];
        int dy = posOtherArea[1] - posDefaultArea[1];
        if (std::sqrt(dx * dx + dy * dy) < (areaToCalculate.getRadius() + area->getRadius())) {
            areaToCalculate.anEntityIsEnterArea(index);
        }
        index += 1;
    }
}
